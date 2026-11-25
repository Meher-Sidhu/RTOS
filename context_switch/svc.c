#include "os.h"

__asm void SVC_Handler(void)
{
    MOVS R0, #4 
    MOV R1, LR
    TST R0, R1
    BEQ Stacking_used_MSP
    MRS R0, PSP
    B SVC_Handler_cont

Stacking_used_MSP
    MRS R0, MSP;

SVC_Handler_cont
    LDR R2, =__cpp(&svc_exc_return)
    MOV R1, LR
    STR R1, [R2]
    BL __cpp(SVC_Handler_C)
    LDR R2, =__cpp(&svc_exc_return)
    LDR R1, [R2]
    BX R1
    ALIGN 4

}
