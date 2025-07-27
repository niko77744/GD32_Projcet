#include "./BSP/Button/Button.h"

static Button bs_btn, wk_btn;

/**
 * @brief       按键初始化函数
 * @param       无
 * @retval      无
 */
void hw_button_init(void)
{
    rcu_periph_clock_enable(BS_GPIO_CLK);   /* 使能KEY_BS时钟 */
    rcu_periph_clock_enable(WKUP_GPIO_CLK); /* 使能WKUP时钟 */

    gpio_mode_set(BS_GPIO_PORT, GPIO_MODE_INPUT, GPIO_PUPD_PULLDOWN, BS_GPIO_PIN);     /* KEY_BS引脚模式设置,下拉输入 */
    gpio_mode_set(WKUP_GPIO_PORT, GPIO_MODE_INPUT, GPIO_PUPD_PULLDOWN, WKUP_GPIO_PIN); /* WKUP引脚模式设置,下拉输入 */
}

// Hardware abstraction layer function
uint8_t read_button_gpio(uint8_t button_id)
{
    switch (button_id)
    {
    case bs_btn_id:
        return gpio_input_bit_get(BS_GPIO_PORT, BS_GPIO_PIN);
    case wk_btn_id:
        return gpio_input_bit_get(WKUP_GPIO_PORT, WKUP_GPIO_PIN);
    default:
        return 0;
    }
}

// Signal handler for graceful exit
void signal_handler(int sig)
{
    if (sig == SIGINT)
    {
        log_i("\nReceived SIGINT, exiting...\n");
    }
}

// Generic event handler that shows button info
void generic_event_handler(Button *btn, const char *event_name)
{
    log_i("Button %d: %s (repeat: %d, pressed: %s)\n",
          btn->button_id,
          event_name,
          button_get_repeat_count(btn),
          button_is_pressed(btn) ? "Yes" : "No");
}

// Event handlers
void on_press_down(Button *btn) { generic_event_handler(btn, "Press Down"); }
void on_press_up(Button *btn) { generic_event_handler(btn, "Press Up"); }
void on_single_click(Button *btn) { generic_event_handler(btn, "Single Click"); }
void on_double_click(Button *btn) { generic_event_handler(btn, "Double Click"); }
void on_long_press_start(Button *btn) { generic_event_handler(btn, "Long Press Start"); }
void on_long_press_hold(Button *btn) { generic_event_handler(btn, "Long Press Hold"); }
void on_press_repeat(Button *btn) { generic_event_handler(btn, "Press Repeat"); }

void buttons_callback_handler(Button *btn)
{
    ButtonEvent event = button_get_event(btn);
    switch (event)
    {
    case BTN_SINGLE_CLICK:
        on_single_click(btn);
        break;
    case BTN_DOUBLE_CLICK:
        on_double_click(btn);
        break;
    case BTN_LONG_PRESS_START:
        on_long_press_start(btn);
        break;
    case BTN_LONG_PRESS_HOLD:
        on_long_press_hold(btn);
        break;
    case BTN_PRESS_REPEAT:
        on_press_repeat(btn);
        break;
    case BTN_PRESS_DOWN:
        on_press_down(btn);
        break;
    case BTN_PRESS_UP:
        on_press_up(btn);
        break;
    default:
        log_i("Unknown event: %d\n", event);
        break;
    }
}

// Initialize a single button with all event handlers
void init_button(Button *handle, uint8_t (*pin_level)(uint8_t), uint8_t button_id, uint8_t active_level, uint8_t enable_all_events)
{
    button_init(handle, pin_level, active_level, button_id);

    if (enable_all_events)
    {
        button_attach(handle, BTN_PRESS_DOWN, buttons_callback_handler);
        button_attach(handle, BTN_PRESS_UP, buttons_callback_handler);
        button_attach(handle, BTN_SINGLE_CLICK, buttons_callback_handler);
        button_attach(handle, BTN_DOUBLE_CLICK, buttons_callback_handler);
        button_attach(handle, BTN_LONG_PRESS_START, buttons_callback_handler);
        button_attach(handle, BTN_LONG_PRESS_HOLD, buttons_callback_handler);
        button_attach(handle, BTN_PRESS_REPEAT, buttons_callback_handler);
    }
    else
    {
        // Only essential events
        button_attach(handle, BTN_SINGLE_CLICK, buttons_callback_handler);
        button_attach(handle, BTN_DOUBLE_CLICK, buttons_callback_handler);
        button_attach(handle, BTN_LONG_PRESS_START, buttons_callback_handler);
    }

    button_start(handle);
}

// Initialize buttons
void buttons_init(void)
{
    // Initialize hardware buttons
    hw_button_init();
    // Initialize bs_btn
    init_button(&bs_btn, read_button_gpio, bs_btn_id, 1, 0);
    // Initialize wk_btn
    init_button(&wk_btn, read_button_gpio, wk_btn_id, 1, 0);
}
