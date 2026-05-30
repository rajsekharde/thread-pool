#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct TaskNode {
    void (*function)(void*);
    void* arg;
    struct TaskNode* next;
} TaskNode;

void pushTask(TaskNode** head, void (*func)(void*), void* arg)
{
    TaskNode* newNode = (TaskNode *)malloc(sizeof(TaskNode));
    newNode->function = func;
    newNode->arg = arg;
    newNode->next = NULL;
    if (!*head) {
        *head = newNode;
        return;
    }
    TaskNode* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void executeAndPopTask(TaskNode** head) {
    if(!*head) {return;}
    TaskNode* temp = *head;
    temp->function(temp->arg);
    *head = (*head)->next;
    free(temp);
}

void printNumber(void* arg) {
    int n = *(int*)arg;
    sleep(2); // sleep 2 seconds
    printf("Number = %d\n", n);
    pthread_exit(NULL);
}

int main() {
    TaskNode* taskList = NULL;
    int b = 100;
    pushTask(&taskList, printNumber, &b);
    int a[5] = {1, 2, 3, 4, 5};
    for(int i=0; i<5; i++) {
        pushTask(&taskList, printNumber, &a[i]);
    }
    
    return 0;
}