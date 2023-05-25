#include "test.h"
#include "led.h"
#include "lvgl.h"

lv_obj_t* tabview;
lv_obj_t* tab1;
lv_obj_t* tab2;
lv_obj_t* tab3;

lv_obj_t* win;

void window(lv_obj_t* far);


static void btn_cb(lv_event_t* e)
{
    //printf("clicked\n");
    // LED_Toggle(LED_D4);
    gpio_set_level(LED_D4, GPIO_LEVEL_HIGH);
    window(tab2);
}

static void switch_cb(lv_event_t* e)
{
    //printf("checked\n");
    LED_Toggle(LED_D5);
}

static void btn_close_cb(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if (code == LV_EVENT_CLICKED)
    {
        gpio_set_level(LED_D4, GPIO_LEVEL_LOW);
        lv_obj_add_flag(win, LV_OBJ_FLAG_HIDDEN);
    }
}

void window(lv_obj_t* far)
{
    //设置窗体
    win = lv_win_create(far, 20);
    lv_obj_set_size(win, 150, 100);
    lv_obj_center(win);
    lv_obj_set_style_border_width(win, 1, LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(win, lv_color_hex(0x8a8a8a), LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(win, 100, LV_STATE_DEFAULT);
    lv_obj_set_style_radius(win, 5, LV_STATE_DEFAULT);

    //设置左侧图标
    lv_obj_t* btnsetting = lv_win_add_btn(win, LV_SYMBOL_SETTINGS, 20);
    lv_obj_set_style_bg_opa(btnsetting, 0, LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(btnsetting, 0, LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(btnsetting, lv_color_hex(0x000000), LV_STATE_DEFAULT);

    //设置标题
    lv_obj_t* title = lv_win_add_title(win, "setting");
    lv_obj_set_style_text_font(title, &lv_font_montserrat_16, LV_STATE_DEFAULT);

    //设置右侧图标
    lv_obj_t * btn_close =  lv_win_add_btn(win, LV_SYMBOL_CLOSE, 20);
    lv_obj_set_style_bg_opa(btn_close, 0, LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(btn_close, 0, LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(btn_close, lv_color_hex(0x000000), LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(btn_close, lv_color_hex(0xff0000), LV_STATE_PRESSED);
    lv_obj_add_event_cb(btn_close, btn_close_cb, LV_EVENT_CLICKED, NULL);  //添加事件响应回调函数

    //设置窗口主体
    lv_obj_t* content = lv_win_get_content(win);
    lv_obj_set_style_bg_color(content, lv_color_hex(0x000f0f), LV_STATE_DEFAULT);

    lv_obj_t* label_obj = lv_label_create(content);     //创建标签
    lv_label_set_text(label_obj, "Hello World!");       //直接设置标签文字
    lv_obj_set_style_bg_color(label_obj, lv_color_hex(0xff0000), LV_STATE_DEFAULT);   //设置背景色
    lv_obj_set_style_bg_opa(label_obj, 100, LV_STATE_DEFAULT);                        //设置背景透明度
    lv_obj_set_style_text_color(label_obj, lv_color_hex(0x00ff00), LV_STATE_DEFAULT); //设置文本颜色
    lv_obj_set_style_text_font(label_obj, &lv_font_montserrat_16, LV_STATE_DEFAULT);  //设置文本字体
}

void TEST_Init(void)
{
    tabview = lv_tabview_create(lv_scr_act(), LV_DIR_TOP, 20);    //创建选项卡
    tab1 = lv_tabview_add_tab(tabview, "Tab1");   //添加选项卡页面
    tab2 = lv_tabview_add_tab(tabview, "Tab2");
    tab3 = lv_tabview_add_tab(tabview, "Tab3");

    /*第一页选项卡*/
    lv_obj_t* switch_obj = lv_switch_create(tab1);  //创建开关
    lv_obj_set_size(switch_obj, 120, 60);           //设置大小
    lv_obj_align(switch_obj, LV_ALIGN_CENTER, 0, 0);//设置位置
    lv_obj_set_style_bg_color(switch_obj, lv_color_hex(0xff00ff), LV_PART_MAIN);    //设置主体颜色
    lv_obj_set_style_bg_color(switch_obj, lv_color_hex(0x00ff00), LV_PART_KNOB);    //设置滑片颜色
    lv_obj_set_style_bg_color(switch_obj, lv_color_hex(0x00ffff), LV_STATE_CHECKED | LV_PART_INDICATOR);//设置状态改变后颜色
    lv_obj_add_state(switch_obj, LV_STATE_CHECKED);// | LV_STATE_DISABLED           //添加状态检测
    lv_obj_add_event_cb(switch_obj, switch_cb, LV_EVENT_VALUE_CHANGED, NULL);       //添加事件响应回调函数

    /*第二页选项卡*/
    lv_obj_t* btn_obj = lv_btn_create(tab2);        //创建按钮
    lv_obj_set_size(btn_obj, 40, 20);               //设置大小
    lv_obj_set_align(btn_obj,LV_ALIGN_CENTER);      //设置位置
    //lv_obj_add_flag(btn_obj, LV_OBJ_FLAG_CHECKABLE);          //添加标志
    lv_obj_add_event_cb(btn_obj,btn_cb,LV_EVENT_CLICKED,NULL);  //添加事件响应回调函数

    /*第三页选项卡*/
    lv_obj_t* label_obj = lv_label_create(tab3);    //创建标签
    // lv_label_set_text(label_obj, "Hello World!"); //直接设置标签文字
    lv_label_set_text_fmt(label_obj, "1+1=%d", 2);  //使用printf的方法设置标签文字
    lv_obj_set_style_bg_color(label_obj,lv_color_hex(0xff0000),LV_STATE_DEFAULT);   //设置背景色
    lv_obj_set_style_bg_opa(label_obj,100,LV_STATE_DEFAULT);                        //设置背景透明度
    lv_obj_set_style_text_color(label_obj,lv_color_hex(0x00ff00),LV_STATE_DEFAULT); //设置文本颜色
    lv_obj_set_style_text_font(label_obj,&lv_font_montserrat_16,LV_STATE_DEFAULT);  //设置文本字体


}



