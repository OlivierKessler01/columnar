#include <stdio.h>
#include <syslog.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_RESPONSE 1000
#define MAX_HOST_LEN 30
#define MAX_PORT_LEN 10
#define DEFAULT_TCP_PORT 3307 
#define MAX_REQ_LEN 100
//void child_reap_handler(int sig)
//{
//    int pid;
//    sig++;
//    while((pid = waitpid(-1, NULL, 0)) != -1) {
//        printf("Child with PID %d terminated", pid);
//    }
//}
static int sock_connect(char* host, int port)
{
    int client_sock;
    int status;
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, host, &serv_addr.sin_addr)
        <= 0) {
        printf(
            "\nInvalid address/ Address not supported \n");
        exit(-1);
    }

    client_sock = socket(AF_INET, SOCK_STREAM,0);
    if(client_sock < 0){
        printf("\n Socket creation error\n");
        exit(-1);
    }

    if ((status
         = connect(client_sock, (struct sockaddr*)&serv_addr,
                   sizeof(serv_addr)))
        < 0) {
        printf("\nConnection Failed \n");
        exit(-1);
    }
    if ((status = connect(client_sock, (struct sockaddr*)&serv_addr,
        sizeof(serv_addr))) < 0) {
        printf("\nConnection Failed \n");
        exit(-1);
    }
    return client_sock;
}

static char* send_request(char* req, int req_len, int client_sock, char* response) {
    send(client_sock, req, req_len, 0);
    printf("\nRequest sent\n");
    read(client_sock, response, 1024 - 1); // subtract 1 for the null
    printf("%sResponse : \n", response);
    return response;
}

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
        //TODO assert that MAX_REQ_LEN is not overlowed
        fgets(req, sizeof(req), stdin);

        if (strcmp(req,"exit\n") == 0)
            exit(EXIT_SUCCESS);

        pipe(pipefd);
        if (fork() == 0){
            //In the child process
            char response[MAX_RESPONSE];
            
            //close the read end of the pipe
            close(pipefd[0]);
            //Add the check that makes sure that THE RESPONSE IS NO MORE THAN
            //MAX_RESPONSE IN LENGTH !!
            //send the result of the server request to the parent process
            int client_sock = sock_connect(host, port);
            send_request(req, strlen(req), client_sock, response);
            write(pipefd[1], response, strlen(response));
            // closing the connected socket
            close(client_sock);
            exit(EXIT_SUCCESS);
        } else {
            //In the parent process
            
            // close the write end of the pipe
            close(pipefd[1]);
            char buf_resp[MAX_RESPONSE]{0};
            int i = 0;
            char b;

            while (read(pipefd[0], &b, 1) > 0){ // read while EOF
                buf_resp[i] = b;
                i++; 
            }
            buf_resp[i] = '\n';

            printf("%s\n",buf_resp);

            //The parent make sure to reap the child process 
            int pid;
            while((pid = waitpid(-1, NULL, 0)) != -1) {
                printf("Child with PID %d terminated\n", pid);
            }
        }
    }

    return 0;
}
