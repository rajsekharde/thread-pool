#include <stdio.h>

#include "taskqueue.h"

// Push task
void push(Task** task_queue, void* (*function) (void*), void* arg) {
    Task* new_task = (Task*)malloc(sizeof(Task));
    if(!new_task) {
        printf("Failed to allocate memory for new task\n");
        return;
    }
    new_task->function = function;
    new_task->arg = arg;
    
    if(!*task_queue) {
        *task_queue = new_task;
        return;
    }
    
    Task* temp = *task_queue;
    while(temp->next) {temp = temp->next;}
    temp->next = new_task;
}

int main() {
    //
}