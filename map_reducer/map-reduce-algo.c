#include "map_reducer.h"
#include "read_file.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void *counter_reducer(void *obj)
{
  int *white_spaces = (int *)calloc(0, sizeof(int));
  string_map_t *string_map = (string_map_t *)obj;
  for (int i = *string_map->init_string; i < *string_map->end_string; i++)
  {
    if (string_map->chars[i] == ' ')
    {
      (*white_spaces)++;
    }
  }
  return (void *)white_spaces;
}

int count_words_mapper(char *string)
{
  int words_amount = 0;

  pthread_t thread1;
  pthread_t thread2;
  pthread_t thread3;

  string_map_t *string_map1;
  string_map_t *string_map2;
  string_map_t *string_map3;

  void *thread1_result = NULL;
  void *thread2_result = NULL;
  void *thread3_result = NULL;

  if (strlen(string) == 0)
    return 0;

  string_map1 = create_string_map(string, 0, (strlen(string) / 3));
  string_map2 = create_string_map(string, (strlen(string) / 3) + 1, (strlen(string) / 3) * 2);
  string_map3 = create_string_map(string, ((strlen(string) / 3) * 2) + 1, strlen(string));

  create_joinable_thread(&thread1, counter_reducer, string_map1);
  create_joinable_thread(&thread2, counter_reducer, string_map2);
  create_joinable_thread(&thread3, counter_reducer, string_map3);

  pthread_join(thread1, &thread1_result);
  pthread_join(thread2, &thread2_result);
  pthread_join(thread3, &thread3_result);

  words_amount = *(int *)thread1_result + *(int *)thread2_result + *(int *)thread3_result + 1;

  release_string_map(string_map1);
  release_string_map(string_map2);
  release_string_map(string_map3);

  free(thread1_result);
  free(thread2_result);
  free(thread3_result);

  return words_amount;
}

int main(int argc, char **argv)
{
  if (argc != 2)
  {
    printf("Usage: %s <file_path>\n", argv[0]);
    return 1;
  }

  const char *file_path = argv[1];
  char *file_content = read_file(file_path);
  if (file_content == NULL) {
      return 1;
  }

  // Counting the words
  int words_amount = count_words_mapper(file_content);

  free(file_content);
  printf("words: %i\n", words_amount);
}
