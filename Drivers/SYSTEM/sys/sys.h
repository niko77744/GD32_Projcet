/**
 ****************************************************************************************************
 * @file        sys.h
 * @version     V1.0
 * @brief       系统初始化代码(包括时钟配置/中断管理/GPIO设置等)
 ****************************************************************************************************
 *
 * V1.0
 * 将头文件包含路径改成相对路径,避免重复设置包含路径的麻烦
 *
 ****************************************************************************************************
 */

#ifndef __SYS_H
#define __SYS_H

/***************************** 标准库头文件包含 *****************************/
#include "gd32h7xx.h"
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdint.h>

/***************************** MiddleWare文件包含 *****************************/
#include "elog.h"
#include "easyflash.h"
#include "multi_button.h"

/***************************** BSP文件包含 *****************************/
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/Button/Button.h"
#include "./BSP/QSPI/qspi.h"

/**
 * SYS_SUPPORT_OS用于定义系统文件夹是否支持OS
 * 0,不支持OS
 * 1,支持OS
 */
#define SYS_SUPPORT_OS 0

/******************************************************************************************/

/* 普通函数 */
void sys_soft_reset(void);   /* 系统软复位 */
void sys_cache_enable(void); /* 使能 Cache */

/* 以下为汇编函数 */
void sys_wfi_set(void);          /* 执行WFI指令 */
void sys_intx_disable(void);     /* 关闭所有中断 */
void sys_intx_enable(void);      /* 开启所有中断 */
void sys_msr_msp(uint32_t addr); /* 设置栈顶地址 */

#endif
