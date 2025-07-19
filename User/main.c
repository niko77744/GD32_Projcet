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

child_led_t red_led = {
    .led = {
        .led_base = {
            .port = GPIOF,                 /* 红色LED所在GPIO端口 */
            .pin = GPIO_PIN_6,             /* 红色LED所在GPIO引脚 */
            .clk = RCU_GPIOF,              /* 红色LED所在GPIO时钟 */
            .gpio_mode = GPIO_MODE_OUTPUT, /* GPIO模式 */
            .otype = GPIO_OTYPE_PP,        /* GPIO输出类型 */
            .ospeed = GPIO_OSPEED_60MHZ,   /* GPIO输出速度 */
            .pull = GPIO_PUPD_NONE,        /* GPIO上下拉 */
            .state = LED_OFF,              /* 初始状态为灭 */
            .active_low = 0,               /* 默认高电平有效 */
        },
    },
};

child_led_t green_led = {
    .led = {
        .led_base = {
            .port = GPIOF,                 /* 蓝色LED所在GPIO端口 */
            .pin = GPIO_PIN_7,             /* 蓝色LED所在GPIO引脚 */
            .clk = RCU_GPIOF,              /* 蓝色LED所在GPIO时钟 */
            .gpio_mode = GPIO_MODE_OUTPUT, /* GPIO模式 */
            .otype = GPIO_OTYPE_PP,        /* GPIO输出类型 */
            .pull = GPIO_PUPD_NONE,        /* GPIO上下拉 */
            .ospeed = GPIO_OSPEED_60MHZ,   /* GPIO输出速度 */
            .state = LED_OFF,              /* 初始状态为灭 */
            .active_low = 0,               /* 默认高电平有效 */
        },
    },
};

int main(void)
{
    sys_cache_enable(); /* 使能CPU cache */
    delay_init(600);    /* 延时初始化 */

    led_t *p_red = register_led_device(&red_led);
    led_t *p_blue = register_led_device(&green_led);

    while (1)
    {
        p_red->set(p_red, LED_ON);
        p_blue->set(p_blue, LED_OFF);
        delay_ms(500);
        p_red->set(p_red, LED_OFF);
        p_blue->set(p_blue, LED_ON);
        delay_ms(500);
    }
}
