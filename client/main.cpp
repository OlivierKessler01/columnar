#include <stdio.h>
#include <syslog.h>
#include <unistd.h>
//#include <signal.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "socket.h" 

#define MAX_RESPONSE 1000
#define MAX_HOST_LEN 30
#define MAX_PORT_LEN 10
#define DEFAULT_TCP_PORT 3307 
#define MAX_REQ_LEN 10000
#define DEFAULT_RESP_SIZE 500
//void child_reap_handler(int sig)
//{
//    int pid;
//    sig++;
//    while((pid = waitpid(-1, NULL, 0)) != -1) {
//        printf("Child with PID %d terminated", pid);
//    }
//}


int main(int argc, char** argv)
{
    char req[MAX_REQ_LEN];
    int pipefd[2];
    char host[MAX_HOST_LEN+1] = {0};
    int port;
    
    if (argc != 3) {
        printf("%s", "The program calling structure should be `columnarc <HOST> <PORT>` .\n");
        exit(-1);
    }

    if (strlen(argv[1]) > MAX_PORT_LEN){
        printf("%s", "Wrong port number.\n");
        exit(EXIT_FAILURE);
    }

    if (strlen(argv[2]) > MAX_HOST_LEN){
        printf("%s", "Hostname too long. \n");
        exit(EXIT_FAILURE);
    }

    strcpy(host, argv[1]); 
    port = atoi(argv[2]);

    //   signal(SIGCHLD, child_reap_handler);
    while (1) {
        printf("> ");
        fgets(req, sizeof(req), stdin);

        if (strcmp(req,"exit\n") == 0)
            exit(EXIT_SUCCESS);

        pipe(pipefd);
        if (fork() == 0){
            //In the child process
            char *response = (char*)malloc(sizeof(char)*1);
            //close the read end of the pipe
            close(pipefd[0]);
            //send the result of the server request to the parent process
            int client_sock = sock_connect(host, port);
            send_request(req, strlen(req), client_sock, response);
            write(pipefd[1], response, strlen(response));
            free(response);
            // closing the connected socket
            close(client_sock);
            exit(EXIT_SUCCESS);
        } else {
            //In the parent process
            
            // close the write end of the pipe
            close(pipefd[1]);
            char *buf_resp = (char *)malloc(sizeof(char)*DEFAULT_RESP_SIZE);
            if(buf_resp == NULL){
                perror("Malloc failed");
                
            }
            int i = 0;
            char* new_buf;
            char b;

            while (read(pipefd[0], &b, 1) > 0){ // read while EOF
                if(i > DEFAULT_RESP_SIZE -2){
                    new_buf = (char*)realloc(buf_resp, i+2);
                    if(new_buf == NULL){
                        perror("Realloc failed");
                        free(buf_resp);
                        free(new_buf);
                        exit(EXIT_FAILURE);
                    }
                }
                buf_resp[i] = b;
                i++; 
            }

            buf_resp[i] = '\n';
            printf("%s\n",buf_resp);
            free(buf_resp);
            free(new_buf);

            //The parent make sure to reap the child process 
            int pid;
            while((pid = waitpid(-1, NULL, 0)) != -1) {
                printf("Child with PID %d terminated\n", pid);
            }
            exit(EXIT_SUCCESS);
        }
    }

    return 0;
}
