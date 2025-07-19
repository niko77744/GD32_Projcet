/**
 ****************************************************************************************************
 * @file        main.c
 * @version     V1.0
 * @brief       跑马灯 实验
 ****************************************************************************************************
 * @attention   Waiken-Smart 慧勤智远
 *
 * 实验平台:    GD32H757ZMT6小系统板
 *
 ****************************************************************************************************
 */

#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"

int main(void)
{
    sys_cache_enable(); /* 使能CPU cache */
    delay_init(600);    /* 延时初始化 */

    while (1)
    {
    }
}
