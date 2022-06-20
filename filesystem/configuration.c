#include "configuration.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clear_buffer(char buffer[], int number_elements) {
    memset(buffer, 0, number_elements);
}

/**
 * Verifies that the parameter exists and that it's value is valid.
 * Then sets it in the configuration object.
 */
int set_configuration_parameter(
        char name_buffer[PARAMETER_NAME_BUFFER_SIZE], 
        char value_buffer[PARAMETER_VALUE_BUFFER_SIZE], 
        struct configuration *config) {
    if(strcmp(name_buffer, "log_file_path") == 0) {
        FILE * log_file_p;
        log_file_p = fopen(value_buffer, "w");

        if (log_file_p == NULL)
        {
            perror("The value provided for log_file_path isn't a writable file.\n");
            exit(EXIT_FAILURE);
        } else {
            config->log_file_path = value_buffer;
        }

        fclose(log_file_p);
    }

    return 0;
}

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
struct configuration load_configuration()
{
    char ch;
    FILE *fp;
    char file_name[30] = "/etc/columnar/columnar.cnf";
    char name_buffer[256];
    int index_name_buffer = 0;
    int result = 0;
    int index_value_buffer = 0;
    char value_buffer[256];
    /* If set to 1, parsing the parameter name, otherwise the parameter value */
    int populate_parameter_name = 1;

    struct configuration config;

    printf("Reading the configuration file\n");
    fp = fopen(file_name, "r");

    if (fp == NULL)
    {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    printf("The contents of %s file is:\n", file_name);

    
    while((ch = fgetc(fp)) != EOF) {
        if(ch == '\n') {
            printf("The value of the parameter is : %s", value_buffer);
            result = set_configuration_parameter(name_buffer, value_buffer, &config);
            if(result == 1) {
                printf("Wrong configuration file formatting.");
            }
            clear_buffer(name_buffer, 256);
            clear_buffer(value_buffer, 256);
            populate_parameter_name = 1;
            index_name_buffer = 0;
            index_value_buffer = 0;
        } else if(ch == '=') {
            printf("Parameter with name : %s detected", name_buffer);
            populate_parameter_name = 0;
            index_value_buffer = 0;
        } else {
            if(populate_parameter_name == 1) {
                name_buffer[index_name_buffer] = ch;
            } else {
                value_buffer[index_value_buffer] = ch;
            }
        }
        printf("%c", ch);
    }

    fclose(fp);
    return config;
}

