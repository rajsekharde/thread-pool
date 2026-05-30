#ifndef THREADPOOL_H
#define THREADPOOL_H

#include "taskqueue.h"
#include "pthread.h"

// Threadpool struct
typedef struct Threadpool {
    int num_threads;
    int is_active;
    Task *task_queue;
    pthread_t* pool;
    pthread_mutex_t* lock;
    pthread_cond_t* signal;
} Threadpool;


#endif THREADPOOL_H