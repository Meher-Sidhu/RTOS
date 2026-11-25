#include "os.h"

__asm void PendSV_Handler(void)
{
    MRS R0, PSP
    SUBS R0, #32
    STMIA R0!, {R4-R7}
    MOV R4, R8
    MOV R5, R9
    MOV R6, R10
    MOV R7, R11
    STMIA R0!, {R4-R7}
    SUBS R0, #32
    MRS R1, CONTROL
    MOVS R2, #1
    ANDS R1, R1, R2
    ORRS R0, R0, R1
    LDR R1, =__cpp(&curr_task)
    LDR R2,[R1]
    ADDS R2, R2
    ADDS R2, R2
    LDR R3, =__cpp(&PSP_array)
    STR R0,[R3, R2]

    LDR R4, =__cpp(&next_task)
    LDR R4,[R4]
    STR R4,[R1]
    ADDS R4, R4
    ADDS R4, R4
    LDR R0, [R3, R4]
    MOVS R1, #1
    ANDS R1, R1, R0
    MSR CONTROL, R1
    MOVS R1, #3
    BICS R0, R0, R1
    ADDS R0, #16
    LDMIA R0!, {R4-R7}
    MOV R8, R4
    MOV R9, R5
    MOV R10, R6
    MOV R11, R7
    MSR PSP, R0
    SUBS R0, #32
    LDMIA R0!, {R4-R7}
    BX LR 
    ALIGN 4

}
