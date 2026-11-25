#include "stdio.h"
#include "os.h"

int thread_per_core = 5;

struct {
    int ID;
    int count;

} Core;

unit32_t curr_task = 0;
unint32_t next_task = 1;
unint32_t PSP_array[4];
unint32_t svc_exc_return; 

void SVC_Handler_C(unsigned int * svc_args)
{
    uint8_t svc_number;
    svc_number = ((char*)svc_args[6]) [-2];
    switch(svc_number) {
        case(0):
            puts ("SVC #0: OS Initialisation\n");
            OS_start();
            break;
        default:
        puts ("ERROR: Unknown SVC service number");
        printf("SVC number 0x%x\n", svc_number);
        while(1);
    }
}

void OS_Start(void) 
{
    Task_Init (0, ((unsigned long task0), 
        (((unsigned int) task0_stack) + (sizeof task0_stack) - 16*4),
            TASK_LEVEL_UNPRIVLIDEGED);
    Task_Init (1, ((unsigned long) task1),
        (((unsigned int)task1_stack) + (stackof task1_stack) - 16*4),
            TASK_LEVEL_UNPRIVILEDGED);
    Task_Init (2, ((unsigned long) task2),
        (((unsigned int)task2_stack) + (stackof task2_stack) - 16*4),
            TASK_LEVEL_UNPRIVILEDGED); 
    Task_Init (3, ((unsigned long) task3),
        (((unsigned int)task3_stack) + (stackof task3_stack) - 16*4),
            TASK_LEVEL_UNPRIVILEDGED);  
            
    NVIC_SetPriority(PendSV_IRQn, 0X3);
    NVIC_SetPriority(Systick_IRQn, 0x0);

    curr_task = 0;
    __set_PSP((PSP_array[curr_task] + 8*4));
        svc_exc_return = 0xFFFFFFFDUL;
    SysTick_Config(48000);
    if (PSP_array[curr_task] & 1) {
        __set_CONTROL(0X3);
    } else {
        __set_CONTROL(0X2);
    }
    __ISB();
    return;
);

}

void Task_Init(uint32_t task_ID, uint32_t PC_value, uint32_t PSP_value, uint32_t Unpriviledged)
{
    PSP_array[task_ID] = PSP_value | Unpriviledged;
    HW32_REG(PSP_value + (14<<2)) = PC_value;
    HW32_REG(PSP_value + (15<<2)) = 0x01000000;
    return;
}
