#pragma once

#define PARAMETER_NAME_BUFFER_SIZE 256
#define PARAMETER_VALUE_BUFFER_SIZE 256
#define DEFAULT_TCP_PORT 3307
#define MAX_REQ_LEN 100

typedef struct configuration {
    char log_file_path[PARAMETER_VALUE_BUFFER_SIZE];
    int  tcp_port;
    int  max_req_len;
} configuration_t;

int load_configuration(configuration_t *config);

void clear_buffer(char buffer[], int number_elements);

int set_configuration_parameter(
        char name_buffer[PARAMETER_NAME_BUFFER_SIZE],
        char value_buffer[PARAMETER_VALUE_BUFFER_SIZE],
        struct configuration *config);

