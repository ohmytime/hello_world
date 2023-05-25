#include "timer.h"
#include "lvgl.h"

// #define TIMER_DIVIDER         16  //  硬件定时器分频器
// #define TIMER_FREQ           (TIMER_BASE_CLK / TIMER_DIVIDER)  // 定时器计数频率

static bool timer_callback(void *args)
{
    BaseType_t pxHigherPriorityTaskWoken = pdFALSE;
    
    lv_tick_inc(1);

    return pxHigherPriorityTaskWoken;
}


void TIMER_Init(uint16_t freq)
{
    timer_config_t config = {
        .alarm_en = 1,
        .counter_en = 0,
        .counter_dir = TIMER_COUNT_UP,
        .auto_reload = 1,
        .divider = 16,
    };
    timer_init(0, 0, &config);
    timer_set_counter_value(0, 0, 0x00ull);
    timer_set_alarm_value(0, 0, 5000000/freq);
    timer_enable_intr(0, 0);
    
    timer_isr_callback_add(0, 0, timer_callback, NULL, ESP_INTR_FLAG_IRAM);

    timer_start(0, 0);
}




