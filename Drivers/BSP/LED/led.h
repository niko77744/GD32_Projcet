/**
 ****************************************************************************************************
 * @file        led.h
 * @version     V1.0
 * @brief       LED ��������
 ****************************************************************************************************
 * @attention   Waiken-Smart ������Զ
 *
 * ʵ��ƽ̨:    GD32H757ZMT6Сϵͳ��
 *
 ****************************************************************************************************
 */

#ifndef __LED_H
#define __LED_H

#include "./SYSTEM/sys/sys.h"

/******************************************************************************************/
/* ���� ���� */

typedef enum
{
    LED_RED = 0,
    LED_GREEN,
    LED_DEVICE_NUM
} led_color_e;

typedef enum
{
    LED_OFF = 0, /* LED�� */
    LED_ON = 1,  /* LED�� */
} led_state_e;

typedef enum
{
    LED_MODE_NORMAL = 0, /* ����ģʽ */
    LED_MODE_BLINK,      /* ��˸ģʽ */
    LED_MODE_BREATH,     /* ����ģʽ */
} led_mode_e;

typedef struct
{
    uint32_t port;       /* LED����GPIO�˿� */
    uint32_t pin;        /* LED����GPIO���� */
    rcu_periph_enum clk; /* LED����GPIOʱ�� */
    uint32_t gpio_mode;  /* GPIOģʽ */
    uint8_t otype;       /* GPIO������� GPIO_OTYPE_PP ����  GPIO_OTYPE_OD ��© */
    uint32_t ospeed;     /* GPIO����ٶ� */
    uint8_t pull;        /* GPIO���������� */
    led_state_e state;   /* LED��ǰ״̬, 1��, 0�� */
    uint8_t active_low;  /* �Ƿ�Ϊ�͵�ƽ��Ч, 0�ߵ�ƽ��Ч, 1�͵�ƽ��Ч 1���� 0���� */
} led_cgf_t;

typedef struct led
{
    led_cgf_t led_base;
    void (*init)(struct led *self);                          /* LED��ʼ������, ����ָ��, �Ա��ڽṹ���е��� */
    void (*set)(struct led *self, led_state_e state);        /* ����LED״̬, 1��, 0�� */
    void (*toggle)(struct led *self);                        /* ��תLED״̬ */
    void (*get_state)(struct led *self, led_state_e *state); /* ��ȡLED״̬, 1��, 0�� */
} led_driver_t;

typedef struct
{
    led_driver_t led;
    void (*init)(led_driver_t *p);                          /* LED��ʼ������ */
    void (*set)(led_driver_t *p, led_state_e state);        /* ����LED״̬, 1��, 0�� */
    void (*toggle)(led_driver_t *p);                        /* ��תLED״̬ */
    void (*get_state)(led_driver_t *p, led_state_e *state); /* ��ȡLED״̬, 1��, 0�� */
} child_led_driver_t;

typedef struct
{
    led_driver_t *led[LED_DEVICE_NUM]; /* LED����ָ�� */
    led_mode_e mode[LED_DEVICE_NUM];   /* LEDģʽ */
} led_app_t;

void led_get_state(led_driver_t *p, led_state_e *state);
void led_set(led_driver_t *p, led_state_e state);
void led_toggle(led_driver_t *p);
void led_init(led_driver_t *p);
led_driver_t *register_led_device(child_led_driver_t *p);
uint8_t delect_led_device(led_driver_t *p);
/******************************************************************************************/

#endif
