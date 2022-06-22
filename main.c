#include "filesystem/configuration.h"
#include "process/daemonize.h"
#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>
#include <unistd.h>

int main()
{
    struct configuration config;
    FILE * user_log_file;

    config = load_configuration();
    build_daemon();
    user_log_file = fopen(config.log_file_path, "w");
    /* TODO : write log to the file*/

    if (user_log_file == NULL)
    {
        perror("The value provided for log_file_path isn't a writable file.\n");
        fclose(user_log_file);
        exit(EXIT_FAILURE);
    }

    fclose(user_log_file);

    while(1)
    {
        /* TODO: Insert daemon code here. */
        syslog(LOG_NOTICE, "First daemon started.");
        sleep(20);
        break;
    }

    /* Log to the syslog */
    syslog(LOG_NOTICE, "First daemon terminated.");
    closelog();

    return EXIT_SUCCESS;
}
