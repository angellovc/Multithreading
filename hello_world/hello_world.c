#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void * thread_fn_callback(void *arg)
{
  char *input = (char*) arg;

  while(1) {
    printf("Input: %s\n", input);
    sleep(3);
  }
}

pthread_t thread1_create()
{
  pthread_t pthread1;

  static char *thread_input1 = "I am thread 1";
  
  /**
  * 0 for sucess
  * any other number for error
  */
  int thread_state = pthread_create(
    &pthread1,
    NULL,
    thread_fn_callback,
    (void *) thread_input1
  );

  if (thread_state != 0)
  {
    printf("Error: Thread could not be created. Error status %d\n", thread_state);
    exit(1);
  }
  return pthread1;
}

int main(int argc, char **argv)
{
  pthread_t thread1 = thread1_create();
  printf("main thread paused\n");
  // pause();
  sleep(6);
  pthread_cancel(thread1);
  return 0;
}