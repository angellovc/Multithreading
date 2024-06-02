#include "map_reducer.h"
#include <stdio.h> 
#include <string.h>


string_map_t* create_string_map(const char *str, int init, int end) {
  // Allocate memory for the struct
  string_map_t *map = (string_map_t *)malloc(sizeof(string_map_t));
  if (map == NULL) {
      printf("Memory allocation for struct failed\n");
      exit(1);
  }

  // Allocate memory for the string
  map->chars = (char *)malloc((strlen(str) + 1) * sizeof(char));
  if (map->chars == NULL) {
      printf("Memory allocation for chars failed\n");
      free(map);
      exit(1);
  }
  strcpy(map->chars, str);

  // Allocate memory for init_string
  map->init_string = (int *)malloc(sizeof(int));
  if (map->init_string == NULL) {
      printf("Memory allocation for init_string failed\n");
      free(map->chars);
      free(map);
      exit(1);
  }
  *(map->init_string) = init;

  // Allocate memory for end_string
  map->end_string = (int *)malloc(sizeof(int));
  if (map->end_string == NULL) {
      printf("Memory allocation for end_string failed\n");
      free(map->chars);
      free(map->init_string);
      free(map);
      exit(1);
  }
  *(map->end_string) = end;

  return map;
}

void release_string_map(string_map_t *map) {
    if (map != NULL) {
        // Free the allocated memory
        if (map->chars != NULL) {
            free(map->chars);
        }
        if (map->init_string != NULL) {
            free(map->init_string);
        }
        if (map->end_string != NULL) {
            free(map->end_string);
        }
        free(map);
    }
}
