#include "configuration.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * This function loads the configuration from the configuration file
 *
 * The configuration file synthax should be of the following form :
 *
 *
 * KEY=VALUE;
 * KEY=VALUE;
 * KEY=VALUE;
 * <EOF>
 */
struct configuration loadconfiguration()
{
    char ch;
    struct configuration config = {};
    FILE *fp;
    char file_name[30] = "/etc/columnar/columnar.cnf";

    printf("Reading the configuration file\n");
    fp = fopen(file_name, "r");

    if (fp == NULL)
    {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    printf("The contents of %s file are:\n", file_name);

    while((ch = fgetc(fp)) != EOF)
        printf("%c", ch);

    fclose(fp);
    return config;
}
