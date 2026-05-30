#ifndef TASKQUEUE_H
#define TASKQUEUE_H

// Task struct
typedef struct Task {
    void* (*function) (void*);
    void* arg;
    struct Task* next;
} Task;

// Push task to Queue
void push(Task** task_queue, void* (*function) (void*), void* arg);

#endif TASKQUEUE_H