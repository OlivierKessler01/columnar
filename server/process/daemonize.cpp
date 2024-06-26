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
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <syslog.h>
#include <string.h>
#include "../filesystem/configuration.h"
#include "../query/runner.h"

#define REQ_BUF_LEN 500

/**
 * child_reap_handler() - Reaps the child zombies 
 */
static void child_reap_handler(int sig)
{
    int child_pid;
    //Potentialy multiple zombies are queued, make sure to reap them all
    while((child_pid = waitpid(-1, NULL, 0)) != -1) {
        syslog(LOG_EMERG, "Child with PID %d terminated.", child_pid);
    }
}

static int process_request(int max_req_len, int accepted_fd){
    int bytes_read;
    int new_size;
    char req_buf[REQ_BUF_LEN] = {0};
    char* dyn_log_buffer;
    char log_buffer[50];

    //Initialize the string that will contain the request
    int req_acc_len = 0;
    char * req_acc = (char*)malloc(sizeof(char)*0);
    if(req_acc == NULL){
        syslog(LOG_EMERG, "Error malloc'ing for request buffer");
        exit(EXIT_FAILURE);
    }
    int len_response = 0;
    char* response = (char*) malloc(0);

    //Read the incoming request
    //
    //TODO : refactor this to use buffer reads to avoid calling read() n times
    //for the n chars of the request.
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
    sprintf(dyn_log_buffer, "Received request: %s", req_acc);
    syslog(LOG_INFO,"Received request: %s", dyn_log_buffer);
    //outputFile << dyn_log_buffer << std::endl;
   
    //Run the query (lexe+parser+build query plan+ run query plan)
    if((len_response = run_query(response, req_acc, req_acc_len)) == -1){
        syslog(LOG_EMERG, "Error realloc'ing for request buffer");
        //outputFile << "Query execution failed." << std::endl;
    }
    free(req_acc);
    free(dyn_log_buffer);
    write(accepted_fd, response, len_response);
    free(response);
    close(accepted_fd);
    return 1;
}

/**
 * run() - Listens on a socker for incoming connections, once
 * one comes, spawns a child process to treat the request.
 */
static int run(int port, int max_req_len, char* log_file_path) {
    int listen_fd;
    __pid_t child_pid;
    int accepted_fd;
    struct sockaddr_in server_addr;
    socklen_t server_addr_len = sizeof(server_addr);

    /* Create the link to the syslog file */
    std::ofstream outputFile(log_file_path, std::ios::app);
    // Check if the file is opened successfully
    if (!outputFile.is_open()) {
        syslog(LOG_ERR, "Failed to open the log file. Check your config and that it is writeable by columnar.");
        exit(EXIT_FAILURE);
    }
   
    //Reap the zombies children if the parent receives a SIGINT
    if (signal(SIGCHLD, child_reap_handler) == SIG_ERR){
        syslog(LOG_EMERG, "Can't add SIGINT signal handler: %s", strerror(errno));
        exit(EXIT_FAILURE);
    }

    // Create a socket
    if ((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        syslog(LOG_EMERG, "Error creating server socket.");
        exit(EXIT_FAILURE);
    }

    // Bind the socket to a port
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port); // Port number
                                        
    if (bind(
        listen_fd, 
        (struct sockaddr *)&server_addr,
        sizeof(server_addr)
    ) < 0) {
        syslog(LOG_EMERG, "Error binding socket");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(listen_fd, 5) < 0) {
        syslog(LOG_EMERG, "Error listening on socket");
        exit(EXIT_FAILURE);
    }

    syslog(LOG_EMERG, "Server listening on port %d , listen_fd : %d", port, listen_fd);
    
    while (1) {
        // Accept incoming connections
        accepted_fd = accept(listen_fd, (struct sockaddr *)&server_addr, &server_addr_len);

        if (accepted_fd < 0) {
            syslog(LOG_EMERG, "Error accept()ing incoming connection: %s", strerror(errno));
            exit(EXIT_FAILURE);
        }

        //A connection has been accepted, run the query in a child process
        if ((child_pid = fork()) < 0) {
            syslog(LOG_EMERG, "Fork() error: %s", strerror(errno));
            exit(EXIT_FAILURE);
        }
        else if(child_pid == 0)
        {
            //In child process 
            // First, close the listening fd
            close(listen_fd);
            process_request(max_req_len, accepted_fd);
            exit(EXIT_SUCCESS);
        }
        else {
            //In parent process
            close(accepted_fd);
        }
    }

    return 0;
}

/**
 * build_daemon() - Forks the current process. Close STDIN, STDOUT and STDERR
 * and launch a loop to make it a daemon.
 */
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

    run(config.tcp_port, config.max_req_len, config.log_file_path);
}


