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
    printf("\nRequest sent\n");
    read(client_sock, response, 1024 - 1); // subtract 1 for the null
    printf("%sResponse : \n", response);
    return response;
}
