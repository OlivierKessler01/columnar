#ifndef FILESYSTEM_CONFIGURATION_H_
#define FILESYSTEM_CONFIGURATION_H_


#define PARAMETER_NAME_BUFFER_SIZE 256
#define PARAMETER_VALUE_BUFFER_SIZE 256
#define DEFAULT_TCP_PORT 3307

typedef struct configuration {
    char log_file_path[PARAMETER_VALUE_BUFFER_SIZE];
    int  tcp_port;
} configuration_t;

int load_configuration(configuration_t *config);

void clear_buffer(char buffer[], int number_elements);

int set_configuration_parameter(
        char name_buffer[PARAMETER_NAME_BUFFER_SIZE],
        char value_buffer[PARAMETER_VALUE_BUFFER_SIZE],
        struct configuration *config);


#endif
