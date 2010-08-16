#include <pthread.h>

#define INTERLOCKED(ops) { pthread_mutex_lock(Receiver->mutex); ops; pthread_mutex_unlock(Receiver->mutex); }
#define INTERLOCK_DECLARATION pthread_mutex_t mutex
#define INTERLOCK_INITIALIZER(name) name->mutex = PTHREAD_MUTEX_INITIALIZER
