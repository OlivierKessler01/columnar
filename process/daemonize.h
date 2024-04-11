#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>
#include "../filesystem/configuration.h"

void build_daemon(configuration_t config);

int open_tcp_socket();
