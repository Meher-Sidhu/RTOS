#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include "task.h"

typedef struct {
    Task* base;  
    Task* top;
    int max;        
} Stack;

int count(Stack *stack);
void initialise(Stack *stack, Task* start, int tasks);
bool push( Stack *stack, Task value );
Task pop( Stack *stack);
void pushinorder(Stack *stack, Task task);

#endif
