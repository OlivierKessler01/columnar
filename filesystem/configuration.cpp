#include "configuration.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

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
        configuration_t *config) {

    if(strcmp(name_buffer, "log_file_path") == 0) {
        FILE * log_file_p;
        log_file_p = fopen(value_buffer, "a");

        if (log_file_p == NULL)
        {
            perror("The value provided for log_file_path in the configuration file"
            " isn't a writable file.\n");
            exit(EXIT_FAILURE);
        } else {
            strcpy(config->log_file_path, value_buffer);
        }

        fclose(log_file_p);
    } else if (strcmp(name_buffer, "tcp_port") == 0) {
        int length;
        int i = 0;
        length = strlen(value_buffer);

        for (i=0;i<length; i++) {
            if (!isdigit(value_buffer[i]))
            {
                perror("The value provided for tcp_port is not an integer.");
            }
        }

        config->tcp_port = atoi(value_buffer);
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
int load_configuration(configuration_t *config)
{
    char ch;
    FILE *fp;
    char file_name[30] = "/etc/columnar/columnar.cnf";
    char name_buffer[256];
    int index_name_buffer = 0;
    int result = 0;
    int index_value_buffer = 0;
    int parsing_comment_line = 0;
    char value_buffer[256];
    /* If set to 1, parsing the parameter name, otherwise the parameter value */
    int populate_parameter_name = 1;

    clear_buffer(name_buffer, PARAMETER_NAME_BUFFER_SIZE);
    clear_buffer(value_buffer, PARAMETER_VALUE_BUFFER_SIZE);
    clear_buffer(config->log_file_path, PARAMETER_VALUE_BUFFER_SIZE);

    printf("Reading the configuration file\n");
    fp = fopen(file_name, "r");

    if (fp == NULL)
    {
        perror("Error while opening the file. Please add /etc/columnar/columnar.cnf\n");
        exit(EXIT_FAILURE);
    }

    while((ch = fgetc(fp)) != EOF) {
        if(ch == '\n') {
            if(parsing_comment_line == 1) {
                printf("Stop parsing the comment line.\n");
                parsing_comment_line = 0;
            } else {
                printf("The value of the parameter is : %s\n", value_buffer);
                result = set_configuration_parameter(name_buffer, value_buffer, config);
                if(result == 1) {
                    printf("Wrong configuration file formatting.\n");
                }

            }
            clear_buffer(name_buffer, 256);
            clear_buffer(value_buffer, 256);
            populate_parameter_name = 1;
            index_name_buffer = 0;
            index_value_buffer = 0;
        } else if(ch == '=') {
            printf("Parameter with name : %s detected\n", name_buffer);
            populate_parameter_name = 0;
        } else if (ch == '#') {
            /* If the line starts with a #, it's a comment line */
            if(index_name_buffer == 0) {
                printf("Parsing a comment line.\n");
                parsing_comment_line = 1;
            }
        } else {
            if(populate_parameter_name == 1) {
                name_buffer[index_name_buffer] = ch;
                index_name_buffer++;
            } else {
                value_buffer[index_value_buffer] = ch;
                index_value_buffer++;
            }
        }
    }

    fclose(fp);

    return 0;
}

