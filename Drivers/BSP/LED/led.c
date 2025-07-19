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
#include "stdlib.h"

static void led_get_state(led_t *p, led_state *state)
{
    if (p == NULL)
    {
        return;
    }
    child_led_t *child = (child_led_t *)p; /* �������ָ��ת��Ϊchild_led_t���� */
    child->get_state(p, state);            /* ��������Ļ�ȡ״̬���� */
}

static void led_set(led_t *p, led_state state)
{
    if (p == NULL)
    {
        return;
    }
    child_led_t *child = (child_led_t *)p; /* �������ָ��ת��Ϊchild_led_t���� */
    child->set(p, state);                  /* �������������״̬���� */
}

static void led_toggle(led_t *p)
{
    if (p == NULL)
    {
        return;
    }
    child_led_t *child = (child_led_t *)p; /* �������ָ��ת��Ϊchild_led_t���� */
    child->toggle(p);                      /* ��������ķ�ת״̬���� */
}

static void led_init(led_t *p)
{
    if (p == NULL)
    {
        return;
    }
    child_led_t *child = (child_led_t *)p; /* �������ָ��ת��Ϊchild_led_t���� */
    p->init = led_init;                    /* ����LED״̬���� */
    p->set = led_set;                      /* ����LED״̬���� */
    p->toggle = led_toggle;                /* ��תLED״̬���� */
    p->get_state = led_get_state;          /* ��ȡLED״̬���� */
    child->init(p);                        /* ��������ĳ�ʼ������ child_led_init */
}

static void get_child_led_state(led_t *p, led_state *state)
{
    if (p == NULL)
    {
        return;
    }
    *state = p->led_base.state; /* ��ȡLED״̬ */
}

static void child_led_set(led_t *p, led_state state)
{
    if (p == NULL)
    {
        return;
    }
    if (p->led_base.active_low)
    {
        state = (led_state)!state; /* ����ǵ͵�ƽ��Ч, ��ת״̬ */
    }
    p->led_base.state = state; /* ����LED״̬ */

    gpio_bit_write(p->led_base.port, p->led_base.pin, state ? SET : RESET);
}

static void child_led_toggle(led_t *p)
{
    if (p == NULL)
    {
        return;
    }
    if (p->led_base.active_low)
    {
        p->led_base.state = (led_state)!p->led_base.state; /* ����ǵ͵�ƽ��Ч, ��ת״̬ */
    }
    else
    {
        p->led_base.state = (led_state)!p->led_base.state; /* ����Ǹߵ�ƽ��Ч, ��ת״̬ */
    }

    gpio_bit_toggle(p->led_base.port, p->led_base.pin); /* ��תLED����״̬ */
}

static void child_led_init(led_t *p)
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

led_t *register_led_device(child_led_t *p)
{
    led_t *led = (led_t *)malloc(sizeof(led_t));
    led = (led_t *)p;
    p->init = child_led_init;
    p->get_state = get_child_led_state;
    p->set = child_led_set;
    p->toggle = child_led_toggle;
    led_init(led);
    return led;
}

uint8_t delect_led_device(led_t *p)
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
