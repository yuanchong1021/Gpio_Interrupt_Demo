/*
 * Copyright 2020-2025 Yuntu Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * 
 * @file flash_ecc_fault.c
 * @brief 
 * 
 */

#include "flash_ecc_fault.h"
#include "interrupt_manager.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/
/* Pointer to runtime state structure.*/
static flash_ecc_fault_state_t * s_FlashEccFaultStatePtr = NULL;

/*******************************************************************************
 * Functions
 ******************************************************************************/
void FLASH_ECC_Fault_Handler_C(hw_stackframe_t *fault_stack);

/* The fault handler is implemented in flash_ecc_fault.s. */
extern void FLASH_ECC_Fault_Handler(void);

static inline bool FLASH_GetUnrecovery(void)
{
    if (EFM->STS & EFM_STS_UNRECOVERR_MASK)
    {
        return true;
    }
#ifdef EFM_STS_CI_UNRECOVERR_MASK
    else if (EFM->STS & EFM_STS_CI_UNRECOVERR_MASK)
    {
        return true;
    }
#endif /* EFM_STS_CI_UNRECOVERR_MASK */
#ifdef EEPROM_STS_UNRECOVERR_MASK
    else if (EEPROM->STS & EEPROM_STS_UNRECOVERR_MASK)
    {
        return true;
    }
#endif /* EEPROM_STS_UNRECOVERR_MASK */
    else
    {
        return false;
    }
}
/**
 * @brief Flash ECC fault C handler.
 *
 * @return void
 */
void FLASH_ECC_Fault_Handler_C(hw_stackframe_t *fault_stack)
{
    DEV_ASSERT(s_FlashEccFaultStatePtr != NULL);

    uint16_t opcode = *((uint16_t *)(fault_stack->pc));
    uint8_t instrSize = 0;

    /* Determine the instruction size based on the opcode. */
    if ((opcode & 0xE800) == 0xE800 ||  /* 32-bit instruction check (pattern 11101x...) */
        (opcode & 0xF000) == 0xF000 ||  /* 32-bit instruction check (pattern 11110x...) */
        (opcode & 0xF800) == 0xF800)    /* 32-bit instruction check (pattern 11111x...) */
    {
        instrSize = 4;
    }
    else
    {
        instrSize = 2;
    }

    /* If the Flash ECC unrecovery error flag is set, skip the faulting instruction. */
    if (FLASH_GetUnrecovery())
    {
        fault_stack->pc += instrSize;
#ifdef SCB_SHCSR_BUSFAULTENA_Msk
        SCB->CFSR = SCB_CFSR_BUSFAULTSR_Msk | SCB_CFSR_PRECISERR_Msk;
#endif /* SCB_SHCSR_BUSFAULTENA_Msk */

        if (s_FlashEccFaultStatePtr->eccCallback != NULL)
        {
            s_FlashEccFaultStatePtr->eccCallback();
        }else{
            /* Do nothing, just jump to next instruction. */
        }
    }
    else
    {
        if(s_FlashEccFaultStatePtr->otherFaultCallback != NULL)
        {
            s_FlashEccFaultStatePtr->otherFaultCallback(fault_stack);
        }else
        {
            /* If other fault callback is not installed, software reset for default. */
            SystemSoftwareReset();
        }
    }
}


/**
 * @brief Flash ECC fault handler initialization.
 *
 * This function initializes the Flash ECC fault handler by setting up the
 * necessary parameters and installing the fault handler.
 *
 * @param userConfigPtr Pointer to the user configuration structure.
 * @param state Pointer to the flash ECC fault state structure.
 *
 * @return void
 */
void FLASH_ECC_Fault_Init(const flash_ecc_fault_config_t * userConfigPtr, flash_ecc_fault_state_t * state)
{
    /* Check the parameters */
    DEV_ASSERT(userConfigPtr != NULL);
    DEV_ASSERT(state != NULL);

    /* Set the state pointer */
    s_FlashEccFaultStatePtr = state;

    /* Set the callback function */
    state->eccCallback = userConfigPtr->eccCallback;
    state->otherFaultCallback = userConfigPtr->otherFaultCallback;

    /* Use FLASH_ECC_Fault_Handler to instead of HardFault_Handler */
    INT_SYS_InstallHandler(HardFault_IRQn, FLASH_ECC_Fault_Handler, NULL);
}
