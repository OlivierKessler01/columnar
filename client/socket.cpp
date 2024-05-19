#include <stdio.h>
#include <syslog.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int sock_connect(char* host, int port)
{
    int client_sock;
    int status;
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, host, &serv_addr.sin_addr) <= 0) {
        printf( "\nInvalid address/ Address not supported \n");
        exit(-1);
    }

    client_sock = socket(AF_INET, SOCK_STREAM,0);
    if(client_sock < 0){
        printf("\n Socket creation error\n");
        exit(-1);
    }

    if ((status = connect(client_sock, (struct sockaddr*)&serv_addr,
        sizeof(serv_addr))) < 0) {
        printf("\nConnection Failed \n");
        exit(-1);
    }

    return client_sock;
}

char* send_request(char* req, int req_len, int client_sock, char* response) {
    send(client_sock, req, req_len, 0);
    char buffer[500];
    ssize_t bytes_read;
    char * new_response;
    int resp_len = 0;
    int new_resp_len;

    while((bytes_read = read(client_sock, buffer, 500)) > 0){
        new_resp_len=resp_len+bytes_read;
        new_response = (char*)realloc(response, new_resp_len);
        if(new_response == NULL){
            printf("\nError realloc'ing for response buffer. \n");
            free(response);
            exit(EXIT_FAILURE);
        }
        response = new_response;

        for (int i =0; i < bytes_read;i++){
            response[i+resp_len] = buffer[i];    
        }
        resp_len=new_resp_len;
    }
    
    new_response = (char*)realloc(response, resp_len+1);
    if(new_response == NULL){
        printf("\nError realloc'ing for response buffer. \n");
        free(response);
        exit(EXIT_FAILURE);
    }
    response = new_response;
    response[resp_len] = '\n';
    return response;
}
