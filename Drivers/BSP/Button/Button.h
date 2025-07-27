#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "./SYSTEM/sys/sys.h"

#define BS_GPIO_PORT GPIOC
#define BS_GPIO_PIN GPIO_PIN_1
#define BS_GPIO_CLK RCU_GPIOC /* GPIOC时钟使能 */

#define WKUP_GPIO_PORT GPIOA
#define WKUP_GPIO_PIN GPIO_PIN_0
#define WKUP_GPIO_CLK RCU_GPIOA /* GPIOA时钟使能 */

typedef enum
{
    bs_btn_id = 1, /* Button 1 */
    wk_btn_id = 2, /* Button 2 */
    max_btn_num,
} btn_id_e;

void buttons_init(void);
void signal_handler(int sig);

#endif /* __BUTTON_H__ */
