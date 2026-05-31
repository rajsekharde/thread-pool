# Thread Pool implementation in C

### Normal multithreaded execution:

A new thread is created for each task. This consumes CPU cycles for initialization and allocates substantial stack memory (8 MB in linux) for each thread. Processing a large number of tasks using this approach will lead to high system resource utilization, context-switching overhead and eventual system failure.

### Threadpool:

A fixed number of worker threads are created at startup and stored in a "pool". Tasks are appended to a shared thread-safe queue. The worker threads pull tasks from the queue one by one, execute them, and return to an idle sleep state when the queue is empty, keeping resource utilization minimal.

## Steps:

### 1. Task queue creation

Task struct:
- Task Function pointer
- Pointer to argument
- Pointer to next node

Queue functions:
- Push a task struct to the end of queue
- Peek the first task in queue
- Pop the first task in queue

### 2. Thread pool creation & initialization

Threadpool struct:
- number of threads
- is_active flag
- task queue
- thread array
- mutex lock
- mutex signal

Thread function execution sequence:
```bash
void* thread_function(void* args) {
    cast args into Threadpool struct
    while(1) {
        lock mutex
        while(pool = active and queue = empty) {
            block thread until task arrives or shutdown occurs
        }
        if(pool = inactive and queue = empty) {
            unlock mutex
            break out of loop
        }
        task = peek(task_queue)
        pop(task_queue)
        unlock mutex
        execute task function
    }
}
```

Threadpool initialization sequence:
```bash
Threadpool* initialize(num_threads) {
    allocate memory for threadpool
    set num_threads, is_active, task_queue = NULL
    initialize mutex
    initialze condition
    allocate memory for thread array
    iterate throught the thread array:
        create thread. pass thread_function, pointer to threadpool
    return threadpool
}
```

### 3. Add tasks to queue

Add task function:
```bash
void add_task(threadpool, function, arg) {
    lock mutex
    push task struct to queue
    send signal to wake up exactly one thread
    unlock mutex
}
```

## Optimizations

The push() function for task queue taks O(n) time. By storing the pointer to last task node, tasks can be added in O(1) time.

## Project structure

- threadpool.c : threadpool source code
- taskqueue.c : task queue implementation
- main.c : import & test threadpool
- *.h : header files
- *.md : documentation/notes

## Running the program

```bash
gcc main.c threadpool.c taskqueue.c
./a.out
```