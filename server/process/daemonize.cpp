#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
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
#include "../filesystem/configuration.h"

#define MAX_REQ_LEN 100

static int open_tcp_socket(int port) {
    int server_sock, clientSocket;
    struct sockaddr_in server_addr;
    socklen_t server_addr_len = sizeof(server_addr);

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
    syslog(LOG_INFO, "Server listening on port %d", port);
    
    int accepted_fd;
    while (1) {
        // Accept incoming connections
        if ((accepted_fd = accept(
            server_sock, (struct sockaddr *)&server_addr, &server_addr_len)
        ) < 0) {
            syslog(LOG_EMERG, "Error accept()ing incoming connection");
            exit(-1);
        }

        syslog(LOG_INFO, "Incoming connection on port %d", port);
        write(accepted_fd, "Ceci vient du server\n", 21);
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

    // Open the file in append mode
    std::ofstream outputFile(config.log_file_path, std::ios::app);

    // Check if the file is opened successfully
    if (!outputFile.is_open()) {
        std::cerr << "Failed to open the file for appending." << std::endl;
        exit(EXIT_FAILURE);
    }

    // Data to append to the file
    std::string newData = "Columnar server daemon running.";

    // Append data to the file
    outputFile << newData << std::endl;
    /* Create the link to the syslog file */
    openlog ("columnar", LOG_PID, LOG_DAEMON);
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

    open_tcp_socket(config.tcp_port);
}


