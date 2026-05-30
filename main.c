#include <stdio.h>
#include <unistd.h>

#include "threadpool.h"

// Args struct
typedef struct Args {
    int val;
} Args;

// Dummy task function
void *print_number(void *arg) {
    Args *a = (Args *)arg;

    printf("Number = %d\n", a->val);
    // fflush(stdout); // display output immediately

    return NULL;
}

int main() {
    Threadpool *t_pool = initialize_threadpool(10);
    if (!t_pool)
    {
        printf("Failed to initialize threadpool\n");
        return 1;
    }

    Args a = {45}, b = {100};
    add_task(t_pool, print_number, &a);
    add_task(t_pool, print_number, &b);

    sleep(2); // main thread sleeps for 2 secs to let the threads execute tasks
    while (1)
    {
        printf("Enter 1 to exit\n");
        int n;
        scanf("%d", &n);
        if (n == 1)
        {
            destroy_threadpool(t_pool);
            break;
        }
    }
    return 0;
}