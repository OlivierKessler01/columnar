#include "filesystem/configuration.h"
#include "process/daemonize.h"
#include <stdio.h>
#include <syslog.h>
#include <unistd.h>

int main()
{
    configuration_t config = {
        "", DEFAULT_TCP_PORT
    };

    load_configuration(&config);

    /** Fork the process and close standard filedescriptors, daemonizing the process */
    build_daemon(config);

    std::ofstream outputFile(config.log_file_path, std::ios::app);

    // Check if the file is opened successfully
    if (!outputFile.is_open()) {
        std::cerr << "Failed to open the file for appending." << std::endl;
        exit(EXIT_FAILURE);
    }

    // Append data to the file
    outputFile << "The daemon is running that." << std::endl;

    while(1)
    {
    }

    /* Log to the syslog */
    syslog(LOG_NOTICE, "First daemon terminated.");
    closelog();

    return 0;
}


