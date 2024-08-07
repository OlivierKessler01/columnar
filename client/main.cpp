#include <stdio.h>
#include <syslog.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include "socket.h" 

#define MAX_RESPONSE 1000
#define MAX_HOST_LEN 30
#define MAX_PORT_LEN 10
#define MAX_REQ_LEN 10000
#define DEFAULT_RESP_SIZE 500

using std::cout, std::endl; 

/**
 * function child_reap_handler - Reap the child process if the parent receives a SIGINT 
 */
static void sigint_handler(__attribute__((unused)) int sig)
{
    //TODO: free resource
}

int main(int argc, char** argv)
{
    char req[MAX_REQ_LEN];
    char host[MAX_HOST_LEN+1] = {0};
    int port;
    int i, child_pid;
    char b;
    
    if (argc != 3) {
        cout << "The program calling structure should be `columnarc <HOST> <PORT>`." << endl;
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
    
    //Reap the children if the parent receives a SIGINT
    if (signal(SIGINT, sigint_handler) == SIG_ERR){
        perror("Can\'t catch SIGINT");
        exit(EXIT_FAILURE);
    }

    char *response = (char*)malloc(sizeof(char)*1);
    while (1) {
        cout << "> ";
        fgets(req, sizeof(req), stdin);

        if (strcmp(req,"exit\n") == 0) {
            free(response);
            exit(EXIT_SUCCESS);
        }

        //In the child process
        //send the result of the server request to the parent process
        int client_sock = sock_connect(host, port);
        if (send_request(req, strlen(req), client_sock, response) < 0){
            perror("Request failed.");
            free(response);
            close(client_sock);
            exit(EXIT_FAILURE);
        }
        cout << response << endl;
        // closing the connected socket
        close(client_sock);
    }

    free(response);
    exit(EXIT_SUCCESS);
    
    return 0;
}
