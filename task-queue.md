# Task Queue implementation in C

Task Node:
```bash
typedef struct TaskNode {
    void (*function)(void*); // Pointer to function
    void* arg; // Pointer to argument for function
    struct TaskNode* next; // Pointer to next node
} TaskNode;
```

Example task:
```bash
void printNumber(void* arg) {
    int a = *(int*)arg;
    printf("Number = %d\n", a);
}
```

Push a task:
```bash
void pushTask(TaskNode** head, void (*func)(void*), void* arg) {
    // Arguments: pointer to first queue node, function, pointer to argument

    // Allocate heap memory for new node
    TaskNode* newNode = (TaskNode*)malloc(sizeof(TaskNode));
    
    // If head is null, new node = head
    if(!*head) {
        *head = newNode;
        return;
    }

    // Iterate to last node
    TaskNode* temp = *head;
    while(temp->next) {temp = temp->next;}

    // Point last node to new node
    temp->next = newNode;
}
```

Execute and pop first task in queue:
```bash
void executeAndPopTask(TaskNode** head) {
    // Check if queue is empty
    if(!*head) {return;}

    // Store first node using temporary pointer
    TaskNode* temp = *head;

    // Call the task function using arg
    temp->function(temp->arg);

    // Move head to next node
    *head = (*head)->next;

    // Free heap memory of first node
    free(temp);
}
```

Use:
```bash
int main() {
    TaskNode* taskQueue = NULL;
    int a = 100;
    pushTask(&taskQueue, printNumber, &a);
    executeAndPopTask(&taskQueue);
    return 0;
}

Output:
Number = 100
```