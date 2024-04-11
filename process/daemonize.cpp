/*
 * daemonize.c
 * This script daemonizes a process.
 */

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

int open_tcp_socket(int port) {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr;
    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);

    // Create a socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        std::cerr << "Error creating socket" << std::endl;
        return 1;
    }

    // Bind the socket to a port
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port); // Port number
    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        syslog(LOG_EMERG, "Error binding socket");
        return 1;
    }

    // Listen for incoming connections
    if (listen(serverSocket, 5) < 0) {
        syslog(LOG_EMERG, "Error listening on socket");
        return 1;
    }
    std::string message = "Server listening on port "+ std::to_string(port);
    syslog(LOG_INFO, "%s",message.c_str());

    // Accept incoming connections
    //clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientAddrLen);
    //if (clientSocket < 0) {
    //    syslog(LOG_EMERG, "Error accepting connection");
    //    return 1;
    //}
    //syslog(LOG_INFO, "Client connected");

    // For simplicity, let's just close the connection
    //close(clientSocket);
    //close(serverSocket);

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
    std::string newData = "Daemon running.";

    // Append data to the file
    outputFile << newData << std::endl;


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

    /* Create the link to the syslog file */
    openlog ("columnar", LOG_PID, LOG_DAEMON);
    
    open_tcp_socket(config.tcp_port);
}


