#pragma once 

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

struct pool { //Represents a pool of connected descriptor
    int maxfd; //Largest descriptor in read_set
    fd_set read_set; //Set of all active (accepted) descriptors
    fd_set ready_set; //Subset of read_set ready for reading (the request)
    int nready; //Number of ready descriptors from select
    int maxi; //Highwater index
    int clientfd[FD_SETSIZE]; //Set of active descriptors
};
