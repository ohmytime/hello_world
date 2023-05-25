#ifndef _LED_H_
#define _LED_H_

#include "sys.h"

#define LED_D4  GPIO_NUM_12
#define LED_D5  GPIO_NUM_13
#define LED_D4_PIN  (1ull << LED_D4)
#define LED_D5_PIN  (1ull << LED_D5)

void LED_Init(void);
void LED_Toggle(gpio_num_t gpio_num);

#endif