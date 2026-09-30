/*
 * Copyright 2020-2026 Yuntu Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * 
 * @file pin_mux.c
 * @brief 
 * 
 */



#include "pin_mux.h"

/*! @brief User configuration cfg InitConfigArr0 array */
const pin_settings_config_t g_pin_mux_InitConfigArr0[NUM_OF_CONFIGURED_PINS0] = {
    /* PTC_9-27-UART1_TX- */
    {
        .base = PCTRLC,
        .pinPortIdx = 9U,
        .pullConfig = PCTRL_INTERNAL_PULL_NOT_ENABLED,
        .passiveFilter = false,
        .driveSelect = PCTRL_LOW_DRIVE_STRENGTH,
        .mux = PCTRL_MUX_ALT2,
        .pinLock = false,
        .intConfig = PCTRL_DMA_INT_DISABLED,
        .clearIntFlag = false,
        .digitalFilter = false,
        .filterConfig ={
            .width = 0U,
        },
        .gpioBase = GPIOC,
        .direction = GPIO_INPUT_DIRECTION,
        .initValue = 0,
    },
    /* PTC_8-28-UART1_RX- */
    {
        .base = PCTRLC,
        .pinPortIdx = 8U,
        .pullConfig = PCTRL_INTERNAL_PULL_NOT_ENABLED,
        .passiveFilter = false,
        .driveSelect = PCTRL_LOW_DRIVE_STRENGTH,
        .mux = PCTRL_MUX_ALT2,
        .pinLock = false,
        .intConfig = PCTRL_DMA_INT_DISABLED,
        .clearIntFlag = false,
        .digitalFilter = false,
        .filterConfig ={
            .width = 0U,
        },
        .gpioBase = GPIOC,
        .direction = GPIO_INPUT_DIRECTION,
        .initValue = 0,
    },
    /* PTB_0-26-GPIO-PTB0 */
    {
        .base = PCTRLB,
        .pinPortIdx = 0U,
        .pullConfig = PCTRL_INTERNAL_PULL_NOT_ENABLED,
        .passiveFilter = false,
        .driveSelect = PCTRL_LOW_DRIVE_STRENGTH,
        .mux = PCTRL_MUX_AS_GPIO,
        .pinLock = false,
        .intConfig = PCTRL_DMA_INT_DISABLED,
        .clearIntFlag = false,
        .digitalFilter = false,
        .filterConfig ={
            .width = 0U,
        },
        .gpioBase = GPIOB,
        .direction = GPIO_INPUT_DIRECTION,
        .initValue = 0,
    },
    /* PTB_1-25-GPIO-PTB1 */
    {
        .base = PCTRLB,
        .pinPortIdx = 1U,
        .pullConfig = PCTRL_INTERNAL_PULL_NOT_ENABLED,
        .passiveFilter = false,
        .driveSelect = PCTRL_LOW_DRIVE_STRENGTH,
        .mux = PCTRL_MUX_AS_GPIO,
        .pinLock = false,
        .intConfig = PCTRL_DMA_INT_DISABLED,
        .clearIntFlag = false,
        .digitalFilter = false,
        .filterConfig ={
            .width = 0U,
        },
        .gpioBase = GPIOB,
        .direction = GPIO_INPUT_DIRECTION,
        .initValue = 0,
    },
    /* PTA_10-44-GPIO-PTA10 */
    {
        .base = PCTRLA,
        .pinPortIdx = 10U,
        .pullConfig = PCTRL_INTERNAL_PULL_NOT_ENABLED,
        .passiveFilter = false,
        .driveSelect = PCTRL_LOW_DRIVE_STRENGTH,
        .mux = PCTRL_MUX_AS_GPIO,
        .pinLock = false,
        .intConfig = PCTRL_DMA_INT_DISABLED,
        .clearIntFlag = false,
        .digitalFilter = false,
        .filterConfig ={
            .width = 0U,
        },
        .gpioBase = GPIOA,
        .direction = GPIO_OUTPUT_DIRECTION,
        .initValue = 0,
    },
    /* PTA_11-43-GPIO-PTA11 */
    {
        .base = PCTRLA,
        .pinPortIdx = 11U,
        .pullConfig = PCTRL_INTERNAL_PULL_NOT_ENABLED,
        .passiveFilter = false,
        .driveSelect = PCTRL_LOW_DRIVE_STRENGTH,
        .mux = PCTRL_MUX_AS_GPIO,
        .pinLock = false,
        .intConfig = PCTRL_DMA_INT_DISABLED,
        .clearIntFlag = false,
        .digitalFilter = false,
        .filterConfig ={
            .width = 0U,
        },
        .gpioBase = GPIOA,
        .direction = GPIO_OUTPUT_DIRECTION,
        .initValue = 0,
    },
    /* PTA_12-42-GPIO-PTA12 */
    {
        .base = PCTRLA,
        .pinPortIdx = 12U,
        .pullConfig = PCTRL_INTERNAL_PULL_NOT_ENABLED,
        .passiveFilter = false,
        .driveSelect = PCTRL_LOW_DRIVE_STRENGTH,
        .mux = PCTRL_MUX_AS_GPIO,
        .pinLock = false,
        .intConfig = PCTRL_DMA_INT_DISABLED,
        .clearIntFlag = false,
        .digitalFilter = false,
        .filterConfig ={
            .width = 0U,
        },
        .gpioBase = GPIOA,
        .direction = GPIO_OUTPUT_DIRECTION,
        .initValue = 0,
    },
};



/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/

