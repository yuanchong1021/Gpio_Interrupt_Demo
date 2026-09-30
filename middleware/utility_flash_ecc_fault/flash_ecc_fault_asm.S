/*
 * Copyright 2020-2025 Yuntu Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * 
 * @file flash_ecc_fault.s
 * @brief 
 * 
 */

    RSEG   .text:CODE(2)
    THUMB

    EXTERN FLASH_ECC_Fault_Handler_C
    PUBLIC FLASH_ECC_Fault_Handler

FLASH_ECC_Fault_Handler
    MOVS    R0, #4                         ; Load immediate 4 into R0 to test LR bit[2]
    MOV     R1, LR                         ; Copy Link Register (LR) into R1
    TST     R1, R0                         ; Test if bit2 of LR (EXC_RETURN[2]) is set
    BNE     get_psp                        ; If bit2 set, exception used PSP -> branch to get_psp
    MRS     R0, MSP                        ; Otherwise, read Main Stack Pointer (MSP) into R0
    B       c_handler                      ; Branch to call the C-level fault handler
get_psp
    MRS     R0, PSP                        ; Read Process Stack Pointer (PSP) into R0
c_handler
    LDR     R2, =FLASH_ECC_Fault_Handler_C ; Load address of C handler into R2
    BX      R2                             ; Branch to address in R2 (call C handler)

    END
