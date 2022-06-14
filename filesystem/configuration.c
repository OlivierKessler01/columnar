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
struct configuration load_configuration()
{
    char ch;
    FILE *fp;
    char file_name[30] = "/etc/columnar/columnar.cnf";
    char name_buffer[256];
    int index_name_buffer = 0;
    int index_value_buffer = 0;
    char value_buffer[256];
    //Is this one is set to 1, parsing the parameter name, otherwise the parameter value
    bool populate_buffer_name = 1;

    struct configuration config;
    config.log_file_path = file_name;

    printf("Reading the configuration file\n");
    fp = fopen(file_name, "r");

    if (fp == NULL)
    {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    printf("The contents of %s file is:\n", file_name);

    // Lines of the config file look like
    // PARAMETER=VALUE
    while((ch = fgetc(fp)) != EOF) {
        if(ch == '\n') {
            printf("The value of the parameter is : %s", value_buffer);
            result = set_configuration_parameter(&name_buffer, &value_buffer, &config);
            if(result == false) {
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
            if(populate_parameter_name = 1) {
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

void clear_buffer(char[] buffer, int number_elements) {
    memset(buffer, 0, numbeer_elements)
}

/**
 * Verifies that the parameter exists and that it's value is valid.
 * Then sets it in the configuration object.
 */
void set_configuration_parameter(char[256], char[256], * struct configuration config) {
    return true;
}
