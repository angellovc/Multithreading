#include <stdio.h>
#include <stdlib.h>
#include "read_file.h"

char* read_file(const char *file_path) {
    // Open the file in read mode
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", file_path);
        return NULL;
    }

    // Get the file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    // Allocate memory for the file contents
    char *buffer = (char *)malloc((file_size + 1) * sizeof(char));
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(file);
        return NULL;
    }

    // Read the file contents into the buffer
    size_t bytesRead = fread(buffer, sizeof(char), file_size, file);
    if (bytesRead != file_size) {
        fprintf(stderr, "Error reading file: %s\n", file_path);
        fclose(file);
        free(buffer);
        return NULL;
    }
    buffer[bytesRead] = '\0';
    fclose(file);

    return buffer;
}
