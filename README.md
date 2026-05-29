# Thread Pool implementation in C

## Task queue creation

Task node struct:
- Function pointer
- Pointer to argument
- Pointer to next node

Queue functions:
- Push a task (function, argument) to the end of queue
- Execute and pop first task in queue