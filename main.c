#include "filesystem/configuration.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    struct configuration config;
    config = load_configuration();
    return 0;
}
