#include "sys.h"
#include "led.h"
#include "timer.h"
#include "lvgl.h"
#include "lv_port_disp_template.h"
#include "lv_port_indev_template.h"
#include "app.h"

void app_main(void)
{
    LED_Init();
    lv_init();
    lv_port_disp_init();
    lv_port_indev_init();
    
    TIMER_Init(1000);

    APP_Init();

    while(true)
    {
        vTaskDelay(5/portTICK_PERIOD_MS);
        lv_timer_handler();
    }
}


