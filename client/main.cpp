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

char* response = NULL;

static void sigint_handler(__attribute__((unused)) int sig)
{
    if(response)
        free(response);
    exit(EXIT_FAILURE);
}

/**
 * process - Connects to the server using TCP, sends the request, prints the response.
 * Returns -1 on error
 */
int process(char* host, int port, char* req, int req_len, char* response)
{
    int client_sock = sock_connect(host, port);
    if (send_request(req, req_len, client_sock, response) < 0){
        cout << "Error while processing the request";
        close(client_sock);
        return -1;
    }
    cout << response << endl;
    close(client_sock);
    return 0;
}

int main(int argc, char** argv)
{
    char req[MAX_REQ_LEN];
    char host[MAX_HOST_LEN+1] = {0};
    int port;
    int i, child_pid;
    char b;
    
    if (argc < 3 || argc > 4) {
        cout << "The program calling structure should be `columnarc <HOST> <PORT>`." << endl;
        cout << "or `columnarc <HOST> <PORT> <REQUEST>`." << endl;
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

    if (argc == 4 && strlen(argv[3]) > MAX_REQ_LEN){
        printf("%s", "Request too long. \n");
        exit(EXIT_FAILURE);
    }

    strcpy(host, argv[1]); 
    port = atoi(argv[2]);

    if (signal(SIGINT, sigint_handler) == SIG_ERR){
        perror("Can\'t catch SIGINT");
        exit(EXIT_FAILURE);
    }

    response = (char*)malloc(sizeof(char)*1);

    if (argc == 3) {
        while (1) {
            cout << "> ";
            fgets(req, sizeof(req), stdin);

            if (strcmp(req,"exit\n") == 0) {
                free(response);
                exit(EXIT_SUCCESS);
            }

            process(host, port, req, strlen(req), response);
        }
    } else {
        strcpy(req, argv[3]);
        strcat(req, "\n");
        process(host, port, req, strlen(argv[3])+1, response);
    }

    free(response);
    exit(EXIT_SUCCESS);
    return 0;
}
