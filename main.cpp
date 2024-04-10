#include "filesystem/configuration.h"
#include "process/daemonize.h"
#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>
#include <unistd.h>

int main()
{
    configuration_t config = {"", DEFAULT_TCP_PORT};

    load_configuration(&config);

    /** Fork the process and close standard filedescriptors, daemonizing the process */
    build_daemon(config.log_file_path);
    while(1)
    {
        printf("the daemon is running that");
        /* TODO: Insert TCP socker listening. */
        syslog(LOG_NOTICE, "First daemon started.");
        break;
    }

    /* Log to the syslog */
    syslog(LOG_NOTICE, "First daemon terminated.");
    closelog();

    return 0;
}


