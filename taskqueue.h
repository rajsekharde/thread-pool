#ifndef TASKQUEUE_H
#define TASKQUEUE_H

// Task struct
typedef struct Task {
    void* (*function) (void*);
    void* arg;
    struct Task* next;
} Task;

#endif TASKQUEUE_H