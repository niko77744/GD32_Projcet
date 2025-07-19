/**
 ****************************************************************************************************
 * @file        main.c
 * @version     V1.0
 * @brief       ����� ʵ��
 ****************************************************************************************************
 * @attention   Waiken-Smart ������Զ
 *
 * ʵ��ƽ̨:    GD32H757ZMT6Сϵͳ��
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

child_led_t green_led = {
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

int main(void)
{
    sys_cache_enable(); /* ʹ��CPU cache */
    delay_init(600);    /* ��ʱ��ʼ�� */

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
