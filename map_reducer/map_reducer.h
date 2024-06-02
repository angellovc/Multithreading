

#include <pthread.h>
#include <stdlib.h>

#ifndef MAP_REDUCER
#define MAP_REDUCER

typedef struct {
    char *chars;
    int *init_string;
    int *end_string;
} string_map_t;

void create_joinable_thread(pthread_t *pthread_handle, void *(*fn_callback)(void*), void *computable_value);

string_map_t* create_string_map(const char *str, int init, int end);

void release_string_map(string_map_t *map);

#endif
