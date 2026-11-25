#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdbool.h>
#include "task.h"
#include "stack.h"

extern int ID;

void Create(int priority, void (*code)(void), Stack *stack);
void Destroy(int ID, Stack *stack);
void suspend (int ID, Stack *stack);
void unsuspend (int ID, Stack *stack);
void print (Stack *stack);
Stack cooperative_context_switch(Stack *stack);
void fault_handler(void);
bool yield(Task* task, Stack *stack);
void non_cooperative_context_switch(Stack *mainstack);

#endif
