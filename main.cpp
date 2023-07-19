#include "filesystem/configuration.h"
#include "process/daemonize.h"
#include "dsa/heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>
#include <unistd.h>

//int main()
//{
//    configuration_t config = {"", DEFAULT_TCP_PORT};
//    FILE * user_log_file;
//
//    load_configuration(&config);
//    user_log_file = fopen(config.log_file_path, "w");
//    /* TODO : write log to the file*/
//
//    if (user_log_file == NULL)
//    {
//        perror("The value provided for log_file_path isn't a writable file.\n");
//        exit(1);
//    } else {
//        fclose(user_log_file);
//    }
//
//    /** Fork the process and close standard filedescriptors, daemonizing the process */
//    build_daemon();
//    while(1)
//    {
//        printf("the daemon is running that");
//        /* TODO: Insert TCP socker listening. */
//        syslog(LOG_NOTICE, "First daemon started.");
//        break;
//    }
//
//    /* Log to the syslog */
//    syslog(LOG_NOTICE, "First daemon terminated.");
//    closelog();
//
//    return 0;
//}


int main() 
{
    test_build_max_heap();
    return 0;
}

