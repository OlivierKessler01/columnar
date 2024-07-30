#pragma once 

#include <stdio.h>
#include <syslog.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int sock_connect(char* host, int port);

int send_request(char* req, int req_len, int client_sock, char* response);
