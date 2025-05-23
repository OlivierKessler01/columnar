#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <sys/syslog.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "daemon.h"
#include <unistd.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <syslog.h>
#include <string.h>
#include "../filesystem/configuration.h"
#include "../query/runner.h"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>
#include "daemon.h"

#define REQ_BUF_LEN 500

/**
 * child_reap_handler() - Reaps the child zombies 
 */
static void child_reap_handler(__attribute__((unused)) int sig)
{
    int child_pid;
    //Potentialy multiple zombies are queued, make sure to reap them all
    while((child_pid = waitpid(-1, NULL, 0)) != -1) {
        syslog(LOG_ERR, "Child with PID %d terminated.", child_pid);
    }
}

static void add_client_async(int connfd, pool *p) {
    int i;
    p->nready--;
    for(i = 0; i < FD_SETSIZE; i++) { //Find an available slot
        if(p->clientfd[i] < 0) {
            p->clientfd[i] = connfd;
            FD_SET(connfd, &p->read_set);
            
            //Update max descriptor and pool highwater mark
            if (connfd > p->maxfd)
                p->maxfd = connfd;
            if(i > p->maxi)
                p->maxi = i;
            break;
        }
    }
    
    //All slots in the pool are filled, too many clients connected
    if(i == FD_SETSIZE) {
        syslog(LOG_ERR, "Too many clients");
        exit(EXIT_FAILURE);
    }
}

static int process_request(configuration_t* config, int accepted_fd){
    int bytes_read;
    int new_size;
    char req_buf[REQ_BUF_LEN] = {0};
    std::string dyn_log_buffer;
    std::string response;
    int req_acc_len = 0;
    int status;
    std::string req_acc = "";

    //Read the incoming request
    //
    //TODO : refactor this to use buffer reads to avoid calling read() n times
    //for the n chars of the request.
    while((bytes_read = read(accepted_fd, req_buf, REQ_BUF_LEN)) > 0){
        new_size = req_acc_len+bytes_read;
        if(new_size > config->max_req_len){
            char text[100];
            sprintf(text, "Request too long, max length : %d", config->max_req_len);
            write(accepted_fd, text, strlen(text));
        }

        for (int i =0; i < bytes_read;i++){
            req_acc+=req_buf[i];
        }
        
        //TODO : Add a timeout in case the client sends a partial request
        //missin the \n
        if(req_acc[req_acc_len -1] == '\n'){
            //The whole request has been transmitted start the parsing process
            break; 
        }
    }
    
    //Run the query (lexe+parser+build query plan+ run query plan)
    if((status = run_query(response, req_acc)) == -1){
        syslog(LOG_ERR, "Error realloc'ing for request buffer");
    }
    write(accepted_fd, response.c_str(), response.size());
    close(accepted_fd);
    return 1;
}

/**
 *
 * process_acync_request - For each ready descriptors in the request descriptor
 * pool, send the response.
 *
 */
static void process_async_request(pool *p, configuration_t* config) {
    int i, connfd;
    
    for (i=0; (i<=p->maxi) && (p->nready > 0); i++) {
        connfd = p->clientfd[i];

        //If the descriptor is ready, return a response to the request
        if ((connfd > 0) && (FD_ISSET(connfd, &p->ready_set))) {
            p->nready--;
            process_request(config, connfd);
            close(connfd);
            //Remove the descriptor from the read_set, the request has been served
            FD_CLR(connfd, &p->read_set);
            p->clientfd[i] = -1;
        }
    }
}

/**
 * run() - Listens on a socket for incoming connections, once
 * one comes, spawns a child process to treat the request.
 */
static int run(configuration* config) {
    int listen_fd;
    __pid_t child_pid;
    int accepted_fd;
    struct sockaddr_in server_addr;
    socklen_t server_addr_len = sizeof(server_addr);
    /* Create the link to the syslog file */
    std::ofstream outputFile(config->log_file_path, std::ios::app);
    int bind_res;
    static pool pool;

    // Check if the file is opened successfully
    if (!outputFile.is_open()) {
        syslog(LOG_ERR, "Failed to open the log file. Check your config and that it is writeable by columnar.");
        exit(EXIT_FAILURE);
    }

    // Create a socket
    if ((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        syslog(LOG_ERR, "Error creating server socket.");
        exit(EXIT_FAILURE);
    }

    // Bind the socket to a port
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(config->tcp_port); // Port number
    bind_res = bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    if (bind_res < 0) {
        syslog(LOG_ERR, "Error binding socket");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(listen_fd, 5) < 0) {
        syslog(LOG_ERR, "Error listening on socket");
        exit(EXIT_FAILURE);
    }

    //syslog(LOG_INFO, "Server listening on port %d , listen_fd : %d", config->tcp_port, listen_fd);
    
    if (strcmp(config->run_mode, MODE_ASYNC) == 0) {
        //////////// ASYNC MODE ///////////////////
        //init pool
        syslog(LOG_INFO, "Async mode");
        int i;
        pool.maxi = -1;
        for(i=0; i<FD_SETSIZE; i++)
            pool.clientfd[i] = -1;
        pool.maxfd = listen_fd;
        FD_ZERO(&pool.read_set);
        FD_SET(listen_fd, &pool.read_set);

        //Process
        while (1) {
            pool.ready_set = pool.read_set;
            pool.nready = select(pool.maxfd+1, &pool.ready_set, NULL,NULL,NULL);

            if (FD_ISSET(listen_fd, &pool.ready_set)) {
                // Accept incoming connections
                accepted_fd = accept(listen_fd, (struct sockaddr *)&server_addr, &server_addr_len);
                if (accepted_fd < 0) {
                    syslog(LOG_ERR, "Error accept()ing incoming connection: %s", strerror(errno));
                    exit(EXIT_FAILURE);
                }
                add_client_async(accepted_fd, &pool);
            }
            
            process_async_request(&pool, config);
        }
    } else if (strcmp(config->run_mode, MODE_PROCESS) == 0) {
        //Reap the zombies children if the parent receives a SIGINT
        if (signal(SIGCHLD, child_reap_handler) == SIG_ERR){
            syslog(LOG_ERR, "Can't add SIGINT signal handler: %s", strerror(errno));
            exit(EXIT_FAILURE);
        }

        while (1) {
            //////////// PROCESS MODE ///////////////////
            // Accept incoming connections
            accepted_fd = accept(listen_fd, (struct sockaddr *)&server_addr, &server_addr_len);

            if (accepted_fd < 0) {
                syslog(LOG_ERR, "Error accept()ing incoming connection: %s", strerror(errno));
                exit(EXIT_FAILURE);
            }

            //A connection has been accepted, run the query in a child process
            if ((child_pid = fork()) < 0) {
                syslog(LOG_ERR, "Fork() error: %s", strerror(errno));
                exit(EXIT_FAILURE);
            }
            else if(child_pid == 0)
            {
                //In child process 
                // First, close the listening fd
                close(listen_fd);
                process_request(config, accepted_fd);
                close(accepted_fd);
                exit(EXIT_SUCCESS);
            }
            else {
                //In parent process
                close(accepted_fd);
            }
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
        syslog(LOG_ERR, "Failed to open the file for appending.");
        exit(EXIT_FAILURE);
    }

    //syslog(LOG_INFO, "Columnar server daemon running.");

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
    for (x = sysconf(_SC_OPEN_MAX); x>=0; x--) {
        close (x);
    }
        
    /* Run the daemon */
    run(&config);
}


