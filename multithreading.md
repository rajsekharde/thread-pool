# Multithreading in C

A standard C program has exactly one thread- the main thread. Threads are created in C using pthreads (POSIX threads), standard on Unix-like systems.

Threads inside a process share the same memory space:
- Share: Code, global variables, static variables, file descriptors, and heap memory.
- Keep private: Each thread gets its own Program Counter, registers, and a private Stack to store local variables and function call history.

System resource usage:
- Stack size: 8 MB for each thread in Linux.

Implementation:
```bash
#include <pthread.h>

// thread function accepting single void* argument and returning void
void action(void* args) {
    // Convert args to required type and perform operation
    pthread_exit(NULL); // exit the thread
}

int main() {
    pthread_t thread; // allocate stack memory for a single pthread_t
    int a = 100; // allocate stack memory for argument

    pthread_create(&thread, NULL, action, &a); // create a thread using the thread variable, function and argument

    pthread_join(thread, NULL); // join the thread to main thread

    return 0;
}
```