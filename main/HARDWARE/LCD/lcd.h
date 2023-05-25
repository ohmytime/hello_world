#ifndef _LCD_H_
#define _LCD_H_

#include "sys.h"

#define USE_HORIZONTAL 0  //设置横屏或者竖屏显示 0或1为竖屏 2或3为横屏

#define LCD_W 240
#define LCD_H 240

#define PIN_RES GPIO_NUM_10
#define PIN_DC  GPIO_NUM_6
#define PIN_BLK GPIO_NUM_11

#define LCD_BLK_SET()   gpio_set_level(PIN_BLK,1);
#define LCD_BLK_CLR()   gpio_set_level(PIN_BLK,0);
#define LCD_RES_SET()   gpio_set_level(PIN_RES,1);
#define LCD_RES_CLR()   gpio_set_level(PIN_RES,0);
#define LCD_DC_SET()    gpio_set_level(PIN_DC,1);
#define LCD_DC_CLR()    gpio_set_level(PIN_DC,0);

void LCD_Init(void);
void LCD_Fill(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t *color);	

#endif

