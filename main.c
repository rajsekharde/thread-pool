#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void delayFunc() {
    int t = 2;
    printf("Sleeping for %d seconds\n", t);
    sleep(t);
}

void* action(void *args) {
    int *a = (int*)args;
    printf("Printing from thread: %d\n", *a);
    delayFunc();
    free(a);
    pthread_exit(NULL);
}

void singleThread() {
    pthread_t myThread;
    int *a = (int*)malloc(sizeof(int));
    *a = 45;
    pthread_create(&myThread, NULL, action, a);
    pthread_join(myThread, NULL);
    printf("Thread finished\n");
}

void multipleThreads(int n) {
    printf("Mutithreaded Execution:\n");
    pthread_t* threadArray = (pthread_t*)malloc(n * sizeof(pthread_t));
    for(int i=0; i<n; i++) {
        int *a = (int*)malloc(sizeof(int));
        *a = i;
        pthread_create(&threadArray[i], NULL, action, a);
    }
    for (int i = 0; i < n; i++) {
        pthread_join(threadArray[i], NULL);
    }
    printf("Thread finished\n");
    free(threadArray);
}

void sequentialExecution(int n) {
    printf("Sequential Execution:\n");
    for(int i=0; i<n; i++) {
        delayFunc();
    }
}

int main() {
    singleThread();
    sequentialExecution(10);
    multipleThreads(10);
    return 0;
}