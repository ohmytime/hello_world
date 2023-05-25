#include "app.h"
#include "lvgl.h"
#include "lv_demos.h"
#include "test.h"

void APP_Init(void)
{
    //lv_demo_music();
    // lv_demo_stress();
    // lv_demo_benchmark();
    // lv_demo_widgets();
    TEST_Init();
}

