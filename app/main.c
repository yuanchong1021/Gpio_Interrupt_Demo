/* USER CODE BEGIN Header */
/* you can remove the copyright */

/*
 *  Copyright 2020-2024 Yuntu Microelectronics Co., Ltd.
 *  All rights reserved.
 * 
 *  SPDX-License-Identifier: BSD-3-Clause
 * 
 * @file main.c
 * @brief 
 * 
 */

/* USER CODE END Header */
#include "sdk_project_config.h"
/* Includes ------------------------------------------------------------------*/
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE BEGIN PD */
#define FB_PTB0_PORT      GPIOB
#define FB_PTB0_PIN       0U

#define FB_PTB1_PORT      GPIOB
#define FB_PTB1_PIN       1U

#define FB_PTA10_PORT     GPIOA
#define FB_PTA10_PIN      10U

#define FB_PTA11_PORT     GPIOA
#define FB_PTA11_PIN      11U

#define FB_PTA12_PORT     GPIOA
#define FB_PTA12_PIN      12U
/* USER CODE END PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
/* USER CODE END PV */

/* Private function declare --------------------------------------------------*/
/* USER CODE BEGIN PFDC */
/* USER CODE END PFDC */
static void Board_Init(void);

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE BEGIN 0 */

static void SetFeedbackOutputs(bool pta10_high, bool pta11_high, bool pta12_high)
{
    PINS_DRV_WritePin(FB_PTA10_PORT, FB_PTA10_PIN, pta10_high ? 1U : 0U);
    PINS_DRV_WritePin(FB_PTA11_PORT, FB_PTA11_PIN, pta11_high ? 1U : 0U);
    PINS_DRV_WritePin(FB_PTA12_PORT, FB_PTA12_PIN, pta12_high ? 1U : 0U);
}

void FeedBackSignalProcessing(void)
{
    bool ptb0_low = (PINS_DRV_ReadPin(FB_PTB0_PORT, FB_PTB0_PIN) == 0U);
    bool ptb1_low = (PINS_DRV_ReadPin(FB_PTB1_PORT, FB_PTB1_PIN) == 0U);

    if (ptb0_low && ptb1_low)
    {
        /* PTB0、PTB1 同时低：PA12 高，PA10/PA11 低 */
        SetFeedbackOutputs(false, false, true);
    }
    else if (ptb0_low)
    {
        /* PTB0 低：PA11 高 */
        SetFeedbackOutputs(false, true, false);
    }
    else if (ptb1_low)
    {
        /* PTB1 低：PA10 高 */
        SetFeedbackOutputs(true, false, false);
    }
    else
    {
        /* 其他情况：全部低 */
        SetFeedbackOutputs(false, false, false);
    }
}
/* USER CODE END 0 */


/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
    /* USER CODE BEGIN 1 */
    /* USER CODE END 1 */ 
    Board_Init();
    /* USER CODE BEGIN 2 */
    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while (1)
    {
        FeedBackSignalProcessing();
        /* USER CODE END WHILE */
        /* USER CODE BEGIN 3 */
    }
    /* USER CODE END 3 */
}

static void Board_Init(void)
{
    CLOCK_SYS_Init(g_clockManConfigsArr,CLOCK_MANAGER_CONFIG_CNT,g_clockManCallbacksArr,CLOCK_MANAGER_CALLBACK_CNT);
    if(STATUS_SUCCESS != CLOCK_SYS_UpdateConfiguration(CLOCK_MANAGER_ACTIVE_INDEX,CLOCK_MANAGER_POLICY_AGREEMENT))
    {
        /* USER CODE BEGIN ERROR_HANDLER 1 */
        SystemSoftwareReset();
        /* USER CODE END ERROR_HANDLER 1 */
    }
    PINS_DRV_Init(NUM_OF_CONFIGURED_PINS0,g_pin_mux_InitConfigArr0);
    UTILITY_PRINT_Init();
    FLASH_ECC_Fault_Init(&flash_ecc_fault_config0,&flash_ecc_fault_config0_State);
}

/* USER CODE BEGIN 4 */
/* USER CODE END 4 */
