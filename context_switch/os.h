#ifndef OS_H
#define OS_H

#include "stdio.h"

extern int thread_per_core;

void Task_Init(uint32_t task_ID, uint32_t PC, uint32_t PSP_value, uint32_t Unpriviledged);
void __svc(0x00) OS_Init(void);
void SVC_Handler_C(unsigned int * svc_args);
void OS_Start(void);

extern unit32_t curr_task;
extern unint32_t next_task;
extern unint32_t PSP_array[4];
extern unint32_t svc_exc_return; 

#endif
