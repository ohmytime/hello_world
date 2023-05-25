#include "led.h"

void LED_Init(void)
{
    gpio_config_t conf = {
        .pin_bit_mask = (1ull << LED_D4) | (1ull << LED_D5),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    gpio_config(&conf);
    gpio_set_level(LED_D4, GPIO_LEVEL_LOW);
    gpio_set_level(LED_D5, GPIO_LEVEL_LOW);
}

void LED_Toggle(gpio_num_t gpio_num)
{
    static u8 state_led_d4 = 0;
    static u8 state_led_d5 = 0;
    if(gpio_num == LED_D4)  {state_led_d4 = !state_led_d4; gpio_set_level(LED_D4, state_led_d4);}
    else                    {state_led_d5 = !state_led_d5; gpio_set_level(LED_D5, state_led_d5);}
}
