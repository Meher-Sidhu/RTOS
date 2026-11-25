#include <stdbool.h>
#include <stdio.h>
#include "scheduler.h"

#define CRASH_SIGNATURE = 0xDEADEEEE;

int ID = 0;

void Create(int priority, void (*code)(void), Stack *stack) {
    Task task;
    task.priority = priority;
    task.code = code;
    task.state = READY;
    int dummyid = ++ID;
    task.id = dummyid;
    pushinorder(stack,task);
}

void Destroy(int ID, Stack *stack) {
    Task arr[(stack->max)/sizeof(Task)];
    Stack stack2; 
    initialise(&stack2, arr, (stack->max)/sizeof(Task));
    while(count(stack)>0) {
        Task task = pop(stack);
        printf("task id is %d", task.id);
        if (task.id == ID) {
            break;
        }
        push(&stack2,task);
    }
    while(count(&stack2)>0) {
        push(stack,pop(&stack2));
    }
}

void suspend (int ID, Stack *stack) { 
    Stack stack2; 
    Task arr[(stack->max)/sizeof(Task)];
    initialise(&stack2, arr, (stack->max)/sizeof(Task));
    while(count(stack)>0) {
        Task task = pop(stack);
        if (task.id == ID) {
            task.state = BLOCKED;
            push(stack,task);
            break;
        }
        else {
            push(&stack2,task);
        }
    }
    while(count(&stack2)>0) {
        push(stack,pop(&stack2));
    }
}

void unsuspend (int ID, Stack *stack) {
    Stack stack2; 
    Task arr[(stack->max)/sizeof(Task)];
    initialise(&stack2, arr, (stack->max)/sizeof(Task));
    while(count(stack)>0) {
        Task task = pop(stack);
        if (task.id == ID) {
            task.state = READY;
            push(stack,task);
            break;
        }
        else {
            push(&stack2,task);
        }
    }
    while(count(&stack2)>0) {
        push(stack,pop(&stack2));
    }
}

void print (Stack *stack) {
    if (stack->top == stack-> base) {
        printf("Stack is empty");
    }
    else {
        Task* ptr = (stack->base);
        for (int i = 1; i <= (count(stack)); i++) {
            Task t = *ptr;
            printf ("Task ID: %d Task State: %d,Task priority: %d\n", t.id,t.state,t.priority);
            ptr++;  
        }

    };
}

Stack cooperative_context_switch(Stack *stack) {
    int num = count(stack); 
    Stack fault_stack;
    Task arr[count(stack)];
    intitialise(&fault_stack, arr,count(stack));
    Task *ptr = stack->top;
    for (int index = 1; index <= num; index++) {
        --ptr;
        ptr->state = RUNNING;
        exception_set_exclusive_handler(HARDFAULT_EXCEPTION, fault_handler);
        int hardfault_check = 0;
        if(watchdog_hw->scratch == CRASH_SIGNATURE) {
            hardfault_check = -1;
            watchdog_hw->scratch = 0;
        }

        if (hardfault_check == -1) {
            ptr->state = FAULTED;
            push(&fault_stack, *ptr);    
        }
        
        if (ptr->state == RUNNING){
            *(ptr->code); 
        }

        else {
            --ptr;
        }
        
    }
    return fault_stack; 
}

void fault_handler(void) {
    watchdog_hw -> scratch = CRASH_SIGNATURE;
    watchdog_reboot(0,0,0)
}

bool yield(Task* task, Stack *stack) {
    suspend(task->id, stack);
    return true;
}

void non_cooperative_context_switch(Stack *mainstack) {
}
