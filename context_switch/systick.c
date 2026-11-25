#include "stdio.h"
#include "os.h"

void Systick_Handler(void){
    switch(curr_task) {
        case(0): next_task = 1; break;
        case(1): next_task = 2; break;
        case(2): next_task = 3; break;
        case(3): next_task = 0; break;
        default: next_task = 0;
            printf("error:ILLEGAL TASK\n");
            while(1);
    }
    if (curr_task != next_task){
        SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
    }
    return;
}
