#include "map_reducer.h"

void create_joinable_thread(pthread_t *pthread_handle, void *(*fn_callback)(void*), void *computable_value)
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
