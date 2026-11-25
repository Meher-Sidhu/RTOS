#include <stdbool.h>
#include <stdio.h>
#include "stack.h"

int count(Stack *stack) {
    return (int)(stack->top - stack->base);
}

void initialise(Stack *stack, Task* start, int tasks){
    stack->base = start; 
    stack->top = stack->base; 
    stack->max = tasks*sizeof(Task);
    return;
}

bool push( Stack *stack, Task value ){

    if ( (stack->top - stack->base)*sizeof(Task) > stack->max ) {
        printf("Stack is full");
        return 0;
    } 
    *((stack->top)++) = value;
    return true;
}

Task pop( Stack *stack){
    if ( stack->top == stack-> base){
        printf("stack is empty");
        Task dummy;
        dummy.id = -1;
        return dummy;
    }
    Task value = *(stack->top - 1);
    --(stack->top);
    return value;
}

void pushinorder(Stack *stack, Task task) {
    if (stack->top == stack-> base) {
        push(stack, task);
        return;
    }

    Stack stack2; 
    Task arr[(stack->max)/sizeof(Task)];
    initialise(&stack2, arr, (stack->max)/sizeof(Task));
    while(count(stack)>0) {
        Task task2 = pop(stack);
        if (task2.priority < task.priority) {
            push(stack,task);
            push(stack, task2);
            break;
        }
        else {
            push(&stack2,task2);
        }
    }
    while(count(&stack2)>0) {
        push(stack,pop(&stack2));
    }
}
