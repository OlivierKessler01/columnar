#include "filesystem/configuration.h"
#include "process/daemonize.h"
#include <syslog.h>
#include <unistd.h>

int main(int argc, char** argv)
{
    configuration_t config = {"", DEFAULT_TCP_PORT, MAX_REQ_LEN};
    load_configuration(&config);
    build_daemon(config);
    return 0;
}


