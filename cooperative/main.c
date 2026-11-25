#include <stdbool.h>
#include <stdio.h>
#include "task.h"
#include "stack.h"
#include "scheduler.h"
#include "code.h"

int main (void) {
    Task Process1;
    Stack task_list;
    int max_task = 10;
    Task arr[max_task];
    initialise(&task_list,arr,max_task);
    Create( 1 ,(void*)code1 , &task_list );
    Create( 3 ,(void*)code3 , &task_list );
    Create( 2 ,(void*)code2 , &task_list );

    print(&task_list);
    printf(" second last to top id %d\n",(task_list.top - 1)->id);
    printf("base id %d\n",(task_list.base)->id);

    Destroy(3,&task_list);
    print(&task_list);

    suspend(1,&task_list);
    Task task = pop(&task_list);
    printf("state %d",task.state);
    push(&task_list,task);

    unsuspend(1,&task_list);
    Task task2 = pop(&task_list);
    printf("state %d",task2.state);
    push(&task_list,task2);

    print(&task_list);


};
