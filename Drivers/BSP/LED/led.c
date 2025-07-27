/**
 ****************************************************************************************************
 * @file        led.c
 * @version     V1.0
 * @brief       LED ��������
 ****************************************************************************************************
 * @attention   Waiken-Smart ������Զ
 *
 * ʵ��ƽ̨:    GD32H757ZMT6Сϵͳ��
 *
 ****************************************************************************************************
 */

#include "./BSP/LED/led.h"

// TIMER22_CH0
child_led_driver_t red_led = {
    .led = {
        .led_base = {
            .port = GPIOF,                 /* ��ɫLED����GPIO�˿� */
            .pin = GPIO_PIN_6,             /* ��ɫLED����GPIO���� */
            .clk = RCU_GPIOF,              /* ��ɫLED����GPIOʱ�� */
            .gpio_mode = GPIO_MODE_OUTPUT, /* GPIOģʽ */
            .otype = GPIO_OTYPE_PP,        /* GPIO������� */
            .ospeed = GPIO_OSPEED_60MHZ,   /* GPIO����ٶ� */
            .pull = GPIO_PUPD_NONE,        /* GPIO������ */
            .state = LED_OFF,              /* ��ʼ״̬Ϊ�� */
            .active_low = 0,               /* Ĭ�ϸߵ�ƽ��Ч */
        },
    },
};
// TIMER22_CH1
child_led_driver_t green_led = {
    .led = {
        .led_base = {
            .port = GPIOF,                 /* ��ɫLED����GPIO�˿� */
            .pin = GPIO_PIN_7,             /* ��ɫLED����GPIO���� */
            .clk = RCU_GPIOF,              /* ��ɫLED����GPIOʱ�� */
            .gpio_mode = GPIO_MODE_OUTPUT, /* GPIOģʽ */
            .otype = GPIO_OTYPE_PP,        /* GPIO������� */
            .pull = GPIO_PUPD_NONE,        /* GPIO������ */
            .ospeed = GPIO_OSPEED_60MHZ,   /* GPIO����ٶ� */
            .state = LED_OFF,              /* ��ʼ״̬Ϊ�� */
            .active_low = 0,               /* Ĭ�ϸߵ�ƽ��Ч */
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
    child_led_driver_t *child = (child_led_driver_t *)p; /* �������ָ��ת��Ϊchild_led_driver_t���� */
    child->get_state(p, state);                          /* ��������Ļ�ȡ״̬���� */
}

void led_set(led_driver_t *p, led_state_e state)
{
    if (p == NULL)
    {
        return;
    }
    child_led_driver_t *child = (child_led_driver_t *)p; /* �������ָ��ת��Ϊchild_led_driver_t���� */
    child->set(p, state);                                /* �������������״̬���� */
}

void led_toggle(led_driver_t *p)
{
    if (p == NULL)
    {
        return;
    }
    child_led_driver_t *child = (child_led_driver_t *)p; /* �������ָ��ת��Ϊchild_led_driver_t���� */
    child->toggle(p);                                    /* ��������ķ�ת״̬���� */
}

void led_init(led_driver_t *p)
{
    if (p == NULL)
    {
        return;
    }
    child_led_driver_t *child = (child_led_driver_t *)p; /* �������ָ��ת��Ϊchild_led_driver_t���� */
    p->init = led_init;                                  /* ����LED״̬���� */
    p->set = led_set;                                    /* ����LED״̬���� */
    p->toggle = led_toggle;                              /* ��תLED״̬���� */
    p->get_state = led_get_state;                        /* ��ȡLED״̬���� */
    child->init(p);                                      /* ��������ĳ�ʼ������ child_led_init */
}

static void get_child_led_state(led_driver_t *p, led_state_e *state)
{
    if (p == NULL)
    {
        return;
    }
    *state = p->led_base.state; /* ��ȡLED״̬ */
}

static void child_led_set(led_driver_t *p, led_state_e state)
{
    if (p == NULL)
    {
        return;
    }
    if (p->led_base.active_low)
    {
        state = (led_state_e)!state; /* ����ǵ͵�ƽ��Ч, ��ת״̬ */
    }
    p->led_base.state = state; /* ����LED״̬ */

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
        p->led_base.state = (led_state_e)!p->led_base.state; /* ����ǵ͵�ƽ��Ч, ��ת״̬ */
    }
    else
    {
        p->led_base.state = (led_state_e)!p->led_base.state; /* ����Ǹߵ�ƽ��Ч, ��ת״̬ */
    }

    gpio_bit_toggle(p->led_base.port, p->led_base.pin); /* ��תLED����״̬ */
}

static void child_led_init(led_driver_t *p)
{
    if (p == NULL)
    {
        return;
    }

    rcu_periph_clock_enable(p->led_base.clk); /* ʹ��LED����GPIOʱ�� */

    /* ����LED����GPIO����ģʽ */
    gpio_mode_set(p->led_base.port, p->led_base.gpio_mode, p->led_base.pull, p->led_base.pin);
    gpio_output_options_set(p->led_base.port, p->led_base.otype, p->led_base.ospeed, p->led_base.pin);

    child_led_set(p, p->led_base.state); /* ����LED��ʼ״̬Ϊ�� */
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
