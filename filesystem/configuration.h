#define PARAMETER_NAME_BUFFER_SIZE 256
#define PARAMETER_VALUE_BUFFER_SIZE 256

typedef struct configuration {
    char* log_file_path;
} configuration_t;

struct configuration load_configuration();

void clear_buffer(char buffer[], int number_elements);

int set_configuration_parameter(
        char name_buffer[PARAMETER_NAME_BUFFER_SIZE],
        char value_buffer[PARAMETER_VALUE_BUFFER_SIZE],
        struct configuration *config);
