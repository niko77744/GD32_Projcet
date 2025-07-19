/**
 ****************************************************************************************************
 * @file        led.h
 * @version     V1.0
 * @brief       LED 驱动代码
 ****************************************************************************************************
 * @attention   Waiken-Smart 慧勤智远
 *
 * 实验平台:    GD32H757ZMT6小系统板
 *
 ****************************************************************************************************
 */

#ifndef __LED_H
#define __LED_H

#include "./SYSTEM/sys/sys.h"

/******************************************************************************************/
/* 引脚 定义 */

typedef enum
{
    LED_OFF = 0, /* LED灭 */
    LED_ON = 1,  /* LED亮 */
} led_state;

typedef struct
{
    uint32_t port;       /* LED所在GPIO端口 */
    uint32_t pin;        /* LED所在GPIO引脚 */
    rcu_periph_enum clk; /* LED所在GPIO时钟 */
    uint32_t gpio_mode;  /* GPIO模式 */
    uint8_t otype;       /* GPIO输出类型 GPIO_OTYPE_PP 推挽  GPIO_OTYPE_OD 开漏 */
    uint32_t ospeed;     /* GPIO输出速度 */
    uint8_t pull;        /* GPIO上下拉配置 */
    led_state state;     /* LED当前状态, 1灭, 0亮 */
    uint8_t active_low;  /* 是否为低电平有效, 0高电平有效, 1低电平有效 1是灭 0是亮 */
} led_base_t;

typedef struct led
{
    led_base_t led_base;
    void (*init)(struct led *self);                        /* LED初始化函数, 传入指针, 以便在结构体中调用 */
    void (*set)(struct led *self, led_state state);        /* 设置LED状态, 1灭, 0亮 */
    void (*toggle)(struct led *self);                      /* 翻转LED状态 */
    void (*get_state)(struct led *self, led_state *state); /* 获取LED状态, 1灭, 0亮 */
} led_t;

typedef struct
{
    led_t led;
    void (*init)(led_t *p);                        /* LED初始化函数 */
    void (*set)(led_t *p, led_state state);        /* 设置LED状态, 1灭, 0亮 */
    void (*toggle)(led_t *p);                      /* 翻转LED状态 */
    void (*get_state)(led_t *p, led_state *state); /* 获取LED状态, 1灭, 0亮 */
} child_led_t;

led_t *register_led_device(child_led_t *p);
uint8_t delect_led_device(led_t *p);
/******************************************************************************************/

#endif
