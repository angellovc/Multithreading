#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

void thread_create(pthread_t *pthread_handle, void *(*fn_callback)(void*), void *computable_value)
{
  pthread_attr_t attr;

  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(
    &attr,
    PTHREAD_CREATE_JOINABLE
  );

  pthread_create(
    pthread_handle,
    &attr,
    fn_callback,
    computable_value
  );

}

void * two_power(void *value)
{
  int number = *((int *)value);
  free(value);

  int start = 0, end = 3;
  while(start < end)
  {
    printf("Calculating second power of %d\n", number);
    start++;
    sleep(3);
  }

  int *second_power = (int *)calloc(1, sizeof(int));
  *second_power = number * number;
  return (void *)second_power;
}

pthread_t pthread2;
pthread_t pthread3;

int main(int argc, char **argv)
{
  void *thread2_result = NULL;
  void *thread3_result = NULL;
  int *thread2_value = (int *)calloc(1, sizeof(int));
  int *thread3_value = (int *)calloc(1, sizeof(int));
  *thread2_value = 2;
  *thread3_value = 10;

  thread_create(
    &pthread2,
    two_power,
    thread2_value
  );

  thread_create(
    &pthread3,
    two_power,
    thread3_value
  );

  pthread_join(pthread2, &thread2_result);
  pthread_join(pthread3, &thread3_result);
  printf("Thread 2 result: %d\n", *((int *)thread2_result));
  printf("Thread 3 result: %d\n", *((int *)thread3_result));

  return 0;
}