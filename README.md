
## 老王ST7789 LVGL测试 

1.3寸240240 IPS液晶屏模块 SPI接口 FT6236电容触摸 全新拆机屏 

## 单片机：
合宙 ESP32C3

## IO接线

```c++

#define PIN_RES GPIO_NUM_10
#define PIN_DC  GPIO_NUM_6
#define PIN_BLK GPIO_NUM_11
//11脚电平一直都是高电平，无法使用普通方法设置成低电平，此时LCD背光一直都是亮的

#define PIN_NUM_MISO -1 //不使用
#define PIN_NUM_MOSI GPIO_NUM_3
#define PIN_NUM_CLK  GPIO_NUM_2
#define PIN_NUM_CS   GPIO_NUM_7


//触摸

#define PIN_NUM_SCL GPIO_NUM_5
#define PIN_NUM_SDA GPIO_NUM_4

#define PIN_TOUCH_NUM_RST   GPIO_NUM_8
#define PIN_TOUCH_NUM_INT   GPIO_NUM_9

## 效果

![图片](https://github.com/ohmytime/hello_world/assets/490477/22d8ab07-825f-4540-8ea5-7a942cd75962)
