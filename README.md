Thread Pool implementation in C

## Threads

A standard C program has exactly one thread- the main thread. Threads are created in C using pthreads (POSIX threads), standard on Unix-like systems.

Threads inside a process share the same memory space:
- Share: Code, global variables, static variables, file descriptors, and heap memory.
- Keep private: Each thread gets its own Program Counter, registers, and a private Stack to store local variables and function call history.

System resource usage:
- Stack size: 8 MB for each thread in Linux.

