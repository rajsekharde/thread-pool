#include <stdio.h>
#include <stdlib.h>

#include "threadpool.h"

// Task function
void* task_function(void* arg) {
    Threadpool* t_pool = (Threadpool*)arg;

    while(1) {
        break;
    }

    return NULL;
}

// Initialize threadpool
Threadpool* initialize_threadpool(int num_threads) {
    Threadpool* t_pool = (Threadpool*)malloc(sizeof(Threadpool));
    if(!t_pool) {
        printf("Failed to allocate memory for Threadpool struct\n");
        return NULL;
    }

    t_pool->num_threads = num_threads;
    t_pool->is_active = 1;
    t_pool->task_queue = NULL;
    
    if(pthread_mutex_init(&t_pool->lock, NULL) != 0) {
        printf("Failed to initialize mutex\n");
        free(t_pool);
        return NULL;
    }

    if(pthread_cond_init(&t_pool->signal, NULL) != 0) {
        printf("Failed to initialize signal\n");
        pthread_mutex_destroy(&t_pool->lock);
        free(t_pool);
        return NULL;
    }

    t_pool->pool = (pthread_t *)malloc(num_threads * sizeof(pthread_t));
    if (!t_pool->pool)
    {
        printf("Failed to allocate memory for pthread_t array\n");
        pthread_cond_destroy(&t_pool->signal);
        pthread_mutex_destroy(&t_pool->lock);
        free(t_pool);
        return NULL;
    }
    for (int i = 0; i < num_threads; i++)
    {
        pthread_create(&t_pool->pool[i], NULL, task_function, (void*)t_pool);
    }

    return t_pool;
}

int main() {
    //
}