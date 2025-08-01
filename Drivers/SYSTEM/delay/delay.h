/**
 ****************************************************************************************************
 * @file        delay.h
 * @version     V1.1
 * @brief       使用SysTick的普通计数模式对延迟进行管理(支持OS)
 *              提供delay_init初始化函数，delay_us和delay_ms等延时函数
 ****************************************************************************************************
 * V1.1
 * 修改SYS_SUPPORT_OS部分代码, 默认仅支持UCOSII 2.93.01版本, 其他OS请参考实现
 * 修改delay_init使用系统时钟
 * 修改delay_us使用时钟摘取法延时, 兼容OS
 * 修改delay_ms直接使用delay_us延时实现.
 *
 ****************************************************************************************************
 */

#ifndef __DELAY_H
#define __DELAY_H

#include "./SYSTEM/sys/sys.h"

/********************************************************************************************/

void delay_init(uint16_t sysclk); /* 初始化延迟函数 */
void delay_ms(uint16_t nms);      /* 延时nms */
void delay_us(uint32_t nus);      /* 延时nus */

#define usleep(nus) delay_us(nus) /* 兼容POSIX的usleep函数 */

#endif
