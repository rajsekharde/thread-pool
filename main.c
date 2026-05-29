#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void* action(void *args) {
    int *a = (int*)args;
    printf("Printing from thread: %d\n", *a);
    sleep(2);
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

void sequentialExecution(int n)
{
    printf("Sequential Execution:\n");
    for (int i = 0; i < n; i++)
    {
        sleep(2);
    }
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

typedef struct Node {
    int val;
    struct Node* next;
} Node;

void push(Node** head, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->val = value;
    newNode->next = NULL;
    if(!*head) {
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while(temp->next != NULL) {temp = temp->next;}
    temp->next = newNode;
}

void pop(Node** head) {
    if(!*head) {return;}
    Node *temp = *head;
    *head = (*head)->next;
    free(temp);
}

void displayQueue(Node* head) {
    if(!head) {return;}
    while(head) {
        printf("%d ", head->val);
        head = head->next;
    }
    printf("\n");
}

int main() {
    Node* head = NULL;
    push(&head, 10);
    push(&head, 20);
    push(&head, 30);
    displayQueue(head);
    pop(&head);
    printf("Front = %d\n", head->val);
    displayQueue(head);
    return 0;
}