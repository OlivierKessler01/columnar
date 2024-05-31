#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <sys/syslog.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "daemonize.h"
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <syslog.h>
#include <string.h>
#include "../filesystem/configuration.h"
#include "../query/runner.h"

#define REQ_BUF_LEN 500

static int process_request(int port, int max_req_len, char* log_file_path) {
    /**
     * Function that opens a socket and waits for an incoming request.
     * When request is intercepted, launchs the query executor.
      */
    int server_sock;
    struct sockaddr_in server_addr;
    socklen_t server_addr_len = sizeof(server_addr);
    int bytes_read;
    int new_size;
    int req_acc_len = 0;
    char* req_acc;
    char req_buf[REQ_BUF_LEN] = {0};
    int accepted_fd;
    char* dyn_log_buffer;
    char log_buffer[50];

    /* Create the link to the syslog file */
    std::ofstream outputFile(log_file_path, std::ios::app);
    // Check if the file is opened successfully
    if (!outputFile.is_open()) {
        syslog(LOG_ERR, "Failed to open the log file. Check your config and that it is writeable by columnar.");
        exit(EXIT_FAILURE);
    }
   

    // Create a socket
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) {
        syslog(LOG_EMERG, "Error creating server socket.");
        exit(-1);
    }

    // Bind the socket to a port
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port); // Port number
    if (bind(
        server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)
    ) < 0) {
        syslog(LOG_EMERG, "Error binding socket");
        exit(-1);
    }

    // Listen for incoming connections
    if (listen(server_sock, 5) < 0) {
        syslog(LOG_EMERG, "Error listening on socket");
        exit(-1);
    }

    sprintf(log_buffer, "Server listening on port %d", port);
    outputFile << log_buffer << std::endl;
    
    while (1) {
        // Accept incoming connections
        if ((accepted_fd = accept(
            server_sock, (struct sockaddr *)&server_addr, &server_addr_len)
        ) < 0) {
            syslog(LOG_EMERG, "Error accept()ing incoming connection");
            exit(-1);
        }

        sprintf(log_buffer, "accept()'d connection on port %d", port);
        outputFile << log_buffer << std::endl;

        //Initialize the string that will contain the request
        req_acc = (char*)malloc(sizeof(char)*0);
        if(req_acc == NULL){
            syslog(LOG_EMERG, "Error malloc'ing for request buffer");
            exit(EXIT_FAILURE);
        }
        req_acc_len = 0;
        memset(req_buf, 0, strlen(req_buf));

        //Read the incoming request
        //Because when the user types /n, 1 char is transmitted,
        //we might wan to change >0 by >1
        //TODO : refactor this
        while((bytes_read = read(accepted_fd, req_buf, REQ_BUF_LEN)) > 0){
            new_size = req_acc_len+bytes_read;
            if(new_size > max_req_len){
                char text[100];
                sprintf(text, "Request too long, max length : %d", max_req_len);
                write(accepted_fd, text, strlen(text));
            }

            req_acc = (char*)realloc(req_acc, new_size);
            if(req_acc == NULL){
                syslog(LOG_EMERG, "Error realloc'ing for request buffer");
                free(req_acc);
                exit(EXIT_FAILURE);
            }

            for (int i =0; i < bytes_read;i++){
                req_acc[i+req_acc_len] = req_buf[i];    
            }
            req_acc_len=new_size;
            
            //The whole request has been transmitted
            //start the parsing process
            if(req_acc[req_acc_len -1] == '\n'){
                break; 
            }
        }
        
        dyn_log_buffer = (char*)malloc(sizeof(char) * new_size+50);
        sprintf(dyn_log_buffer, "Received request: \"%s\"\n", req_acc);
        outputFile << dyn_log_buffer << std::endl;
       
        //Run the query (lexe+parser+build query plan+ run query plan)
        int len_response;
        char * response = run_query(&len_response, req_acc, req_acc_len);
        free(req_acc);
        write(accepted_fd, response, len_response);
        free(response);
        close(accepted_fd);
    }

    return 0;
}

void build_daemon(configuration_t config)
{
    pid_t pid;
    int x;

    /* Fork off the parent process */
    pid = fork();

    /* An error occurred */
    if (pid < 0)
        exit(EXIT_FAILURE);

    /* Success: Let the parent terminate */
    if (pid > 0)
        exit(EXIT_SUCCESS);

    /* Create the link to the syslog file */
    std::ofstream outputFile(config.log_file_path, std::ios::app);

    // Check if the file is opened successfully
    if (!outputFile.is_open()) {
        outputFile << "Failed to open the file for appending." << std::endl;
        exit(EXIT_FAILURE);
    }

    // Data to append to the file
    std::string newData = "Columnar server daemon running.";

    // Append data to the file
    outputFile << newData << std::endl;
    syslog(LOG_INFO, "%s", newData.c_str());


    /* On success: The child process becomes session leader */
    if (setsid() < 0)
        exit(EXIT_FAILURE);

    /* Catch, ignore and handle signals */
    /* TODO: Implement a working signal handler */
    signal(SIGCHLD, SIG_IGN);
    signal(SIGHUP, SIG_IGN);

    /* Fork off for the second time*/
    pid = fork();

    /* An error occurred */
    if (pid < 0)
        exit(EXIT_FAILURE);

    /* Success: Let the parent terminate */
    if (pid > 0)
        exit(EXIT_SUCCESS);

    /* Set new file permissions */
    umask(0);

    /* Change the working directory to the root directory */
    /* or another appropriated directory */
    chdir("/");

    /* Close stdin, stderr, stdout file descriptors*/
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    /* Close all open file descriptors */
    for (x = sysconf(_SC_OPEN_MAX); x>=0; x--)
    {
        close (x);
    }

    process_request(config.tcp_port, config.max_req_len, config.log_file_path);
}


