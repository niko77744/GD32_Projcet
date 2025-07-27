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
#include "./BSP/Button/Button.h"
#include "elog.h"

int main(void)
{
    sys_cache_enable(); /* 使能CPU cache */
    delay_init(600);    /* 延时初始化 */
    usart_init(115200); /* 初始化USART */

    elog_init();
    /* set EasyLogger log format */
    elog_set_fmt(ELOG_LVL_ASSERT, ELOG_FMT_ALL);
    elog_set_fmt(ELOG_LVL_ERROR, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
    elog_set_fmt(ELOG_LVL_WARN, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
    elog_set_fmt(ELOG_LVL_INFO, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
    elog_set_fmt(ELOG_LVL_DEBUG, ELOG_FMT_ALL & ~(ELOG_FMT_FUNC | ELOG_FMT_T_INFO | ELOG_FMT_P_INFO));
    elog_set_fmt(ELOG_LVL_VERBOSE, ELOG_FMT_ALL & ~(ELOG_FMT_FUNC | ELOG_FMT_T_INFO | ELOG_FMT_P_INFO));
    /* start EasyLogger */
    elog_start();

    log_i("MultiButton Library Basic Example");
    log_i("=====================================");

    // Set up signal handler
    signal(SIGINT, signal_handler);

    // Initialize buttons
    buttons_init();
    log_i("Buttons initialized successfully\n\n");

    log_i("Demo sequence:\n");
    log_w("1. Single click simulation\n");
    log_i("2. Double click simulation\n");
    log_i("3. Long press simulation\n");
    log_i("4. Repeat press simulation\n\n");

    while (1)
    {
        button_ticks();
        usleep(5000); // 5ms delay
    }
}
