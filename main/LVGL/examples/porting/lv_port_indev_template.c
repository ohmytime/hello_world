#if 1

#include "lv_port_indev_template.h"
#include "lvgl.h"
#include "touch.h"
#include "iic.h"

static void touchpad_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);

lv_indev_t * indev_touchpad;

void lv_port_indev_init(void)
{
    static lv_indev_drv_t indev_drv;

    IIC_Init();
    TOUCH_Init();

    /*Register a touchpad input device*/
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = touchpad_read;
    indev_touchpad = lv_indev_drv_register(&indev_drv);
}

/*Will be called by the library to read the touchpad*/
static void touchpad_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{
    static lv_coord_t last_x = 0;
    static lv_coord_t last_y = 0;

    /*Save the pressed coordinates and the state*/
    //TOUCH_Scan();
    if(TPR_Structure.TouchInt == true)
    {
        TOUCH_Scan();
        if(TPR_Structure.TouchSta & TP_PRES_DOWN)
        {
            last_x = TPR_Structure.x[0];
            last_y = TPR_Structure.y[0];
            data->state = LV_INDEV_STATE_PR;
        }
        else
            data->state = LV_INDEV_STATE_REL;
        TPR_Structure.TouchInt = false;
    }
    else
        data->state = LV_INDEV_STATE_REL;

    /*Set the last pressed coordinates*/
    data->point.x = last_x;
    data->point.y = last_y;
}

#else /*Enable this file at the top*/

/*This dummy typedef exists purely to silence -Wpedantic.*/
typedef int keep_pedantic_happy;
#endif
