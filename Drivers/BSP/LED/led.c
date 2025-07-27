/**
 ****************************************************************************************************
 * @file        led.c
 * @version     V1.0
 * @brief       LED 驱动代码
 ****************************************************************************************************
 * @attention   Waiken-Smart 慧勤智远
 *
 * 实验平台:    GD32H757ZMT6小系统板
 *
 ****************************************************************************************************
 */

#include "./BSP/LED/led.h"

// TIMER22_CH0
child_led_driver_t red_led = {
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
// TIMER22_CH1
child_led_driver_t green_led = {
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

led_driver_t *p_red;
led_driver_t *p_green;

led_app_t led_app = {
    .led = {
        [LED_RED] = NULL,
        [LED_GREEN] = NULL,
    },
    .mode = {
        LED_MODE_NORMAL,
        LED_MODE_NORMAL,
    },
};

void led_get_state(led_driver_t *p, led_state_e *state)
{
    if (p == NULL)
    {
        return;
    }
    child_led_driver_t *child = (child_led_driver_t *)p; /* 将传入的指针转换为child_led_driver_t类型 */
    child->get_state(p, state);                          /* 调用子类的获取状态函数 */
}

void led_set(led_driver_t *p, led_state_e state)
{
    if (p == NULL)
    {
        return;
    }
    child_led_driver_t *child = (child_led_driver_t *)p; /* 将传入的指针转换为child_led_driver_t类型 */
    child->set(p, state);                                /* 调用子类的设置状态函数 */
}

void led_toggle(led_driver_t *p)
{
    if (p == NULL)
    {
        return;
    }
    child_led_driver_t *child = (child_led_driver_t *)p; /* 将传入的指针转换为child_led_driver_t类型 */
    child->toggle(p);                                    /* 调用子类的翻转状态函数 */
}

void led_init(led_driver_t *p)
{
    if (p == NULL)
    {
        return;
    }
    child_led_driver_t *child = (child_led_driver_t *)p; /* 将传入的指针转换为child_led_driver_t类型 */
    p->init = led_init;                                  /* 设置LED状态函数 */
    p->set = led_set;                                    /* 设置LED状态函数 */
    p->toggle = led_toggle;                              /* 翻转LED状态函数 */
    p->get_state = led_get_state;                        /* 获取LED状态函数 */
    child->init(p);                                      /* 调用子类的初始化函数 child_led_init */
}

static void get_child_led_state(led_driver_t *p, led_state_e *state)
{
    if (p == NULL)
    {
        return;
    }
    *state = p->led_base.state; /* 获取LED状态 */
}

static void child_led_set(led_driver_t *p, led_state_e state)
{
    if (p == NULL)
    {
        return;
    }
    if (p->led_base.active_low)
    {
        state = (led_state_e)!state; /* 如果是低电平有效, 则翻转状态 */
    }
    p->led_base.state = state; /* 更新LED状态 */

    gpio_bit_write(p->led_base.port, p->led_base.pin, state ? SET : RESET);
}

static void child_led_toggle(led_driver_t *p)
{
    if (p == NULL)
    {
        return;
    }
    if (p->led_base.active_low)
    {
        p->led_base.state = (led_state_e)!p->led_base.state; /* 如果是低电平有效, 则翻转状态 */
    }
    else
    {
        p->led_base.state = (led_state_e)!p->led_base.state; /* 如果是高电平有效, 则翻转状态 */
    }

    gpio_bit_toggle(p->led_base.port, p->led_base.pin); /* 翻转LED引脚状态 */
}

static void child_led_init(led_driver_t *p)
{
    if (p == NULL)
    {
        return;
    }

    rcu_periph_clock_enable(p->led_base.clk); /* 使能LED所在GPIO时钟 */

    /* 设置LED所在GPIO引脚模式 */
    gpio_mode_set(p->led_base.port, p->led_base.gpio_mode, p->led_base.pull, p->led_base.pin);
    gpio_output_options_set(p->led_base.port, p->led_base.otype, p->led_base.ospeed, p->led_base.pin);

    child_led_set(p, p->led_base.state); /* 设置LED初始状态为灭 */
}

led_driver_t *register_led_device(child_led_driver_t *p)
{
    led_driver_t *led = (led_driver_t *)malloc(sizeof(led_driver_t));
    led = (led_driver_t *)p;
    p->init = child_led_init;
    p->get_state = get_child_led_state;
    p->set = child_led_set;
    p->toggle = child_led_toggle;
    led_init(led);
    return led;
}

uint8_t delect_led_device(led_driver_t *p)
{
    if (p == NULL)
    {
        return 0;
    }
    else
    {
        free(p);
        p->get_state = NULL;
        p->init = NULL;
        p->set = NULL;
        p->toggle = NULL;
        return 1;
    }
}

void led_app_handle(void)
{
    p_red = register_led_device(&red_led);
    p_green = register_led_device(&green_led);

    // led_set(p_red, LED_ON);
    // led_set(p_green, LED_ON);
    // delay_ms(500);
    // led_set(p_red, LED_OFF);
    // led_set(p_green, LED_OFF);
    // delay_ms(500);
}
