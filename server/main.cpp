#include "filesystem/configuration.h"
#include "process/daemonize.h"
#include <syslog.h>
#include <unistd.h>

int main()
{
    configuration_t config = {
        "",
        DEFAULT_TCP_PORT,
        MAX_REQ_LEN,
        DEFAULT_RUN_MODE
    };
    load_configuration(&config);
    syslog(LOG_INFO, "Server run mode : %s", config.run_mode);
    build_daemon(config);
    return 0;
}


