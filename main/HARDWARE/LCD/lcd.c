#include "lcd.h"
#include "spi.h"

void LCD_WR_DATA8(uint8_t data)
{
	LCD_DC_SET();//写数据
	SPI_Sent_Byte(data);
}

void LCD_WR_DATA(uint16_t data)
{
	LCD_DC_SET();//写数据
	SPI_Sent_Byte(data>>8);
	SPI_Sent_Byte(data);
}

void LCD_WR_REG(uint8_t data)
{
	LCD_DC_CLR();//写命令
	SPI_Sent_Byte(data);
}

void LCD_Address_Set(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
#if USE_HORIZONTAL == 0
	LCD_WR_REG(0x2a);//列地址设置
	LCD_WR_DATA(x1);
	LCD_WR_DATA(x2);
	LCD_WR_REG(0x2b);//行地址设置
	LCD_WR_DATA(y1);
	LCD_WR_DATA(y2);
	LCD_WR_REG(0x2c);//储存器写
#elif USE_HORIZONTAL == 1
	LCD_WR_REG(0x2a);//列地址设置
	LCD_WR_DATA(x1);
	LCD_WR_DATA(x2);
	LCD_WR_REG(0x2b);//行地址设置
	LCD_WR_DATA(y1+80);
	LCD_WR_DATA(y2+80);
	LCD_WR_REG(0x2c);//储存器写
#elif USE_HORIZONTAL==2
	LCD_WR_REG(0x2a);//列地址设置
	LCD_WR_DATA(x1);
	LCD_WR_DATA(x2);
	LCD_WR_REG(0x2b);//行地址设置
	LCD_WR_DATA(y1);
	LCD_WR_DATA(y2);
	LCD_WR_REG(0x2c);//储存器写
#else
	LCD_WR_REG(0x2a);//列地址设置
	LCD_WR_DATA(x1+80);
	LCD_WR_DATA(x2+80);
	LCD_WR_REG(0x2b);//行地址设置
	LCD_WR_DATA(y1);
	LCD_WR_DATA(y2);
	LCD_WR_REG(0x2c);//储存器写
#endif
}

#define MAX_ROW_NUM	4800	//(LCD_W * 10(行) * 2(byte))
#define STEP		2400	//(LCD_W * 10(行))
IRAM_ATTR void LCD_Fill(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t *color)	
{
	uint32_t len = (x2 + 1 - x1) * (y2 + 1 - y1) * 2;
	if (len == 0)	return;

	LCD_Address_Set(x1, y1, x2, y2);
	LCD_DC_SET();
	uint32_t times = len / MAX_ROW_NUM;
	uint32_t rest = len % MAX_ROW_NUM;
	int i = 0;
	
	if(times > 0)
	{
		times -= 1;
		for (i = 0; i < times; i++)
		{
			SPI_Sent_Queue(color, STEP * 16, USER_TRANS_STA_CONTINUE);
			color += STEP;
		}
		if(rest == 0)
		{
			SPI_Sent_Queue(color, STEP * 16, USER_TRANS_STA_OVER);
			return;
		}
		else
		{
			SPI_Sent_Queue(color, STEP * 16, USER_TRANS_STA_CONTINUE);
			color += STEP;
		}
	}
	SPI_Sent_Queue(color, rest * 8, USER_TRANS_STA_OVER);
}

void LCD_GPIO_Init(void)
{
	gpio_reset_pin(PIN_RES);
	gpio_reset_pin(PIN_DC);
	gpio_reset_pin(PIN_BLK);

	gpio_set_direction(PIN_RES, GPIO_MODE_OUTPUT);
	gpio_set_direction(PIN_DC, GPIO_MODE_OUTPUT);
	gpio_set_direction(PIN_BLK, GPIO_MODE_OUTPUT);

	gpio_set_level(PIN_RES, GPIO_LEVEL_HIGH);
	gpio_set_level(PIN_DC,  GPIO_LEVEL_HIGH);
    gpio_set_level(PIN_BLK, GPIO_LEVEL_HIGH);
}

void LCD_Init(void)
{
	LCD_GPIO_Init();
	vTaskDelay(200/portTICK_PERIOD_MS);
	
	LCD_RES_CLR();
	vTaskDelay(200/portTICK_PERIOD_MS);
	LCD_RES_SET();
	vTaskDelay(200/portTICK_PERIOD_MS);
	LCD_BLK_SET();
	vTaskDelay(200/portTICK_PERIOD_MS);
	
	LCD_WR_REG(0x11); //Sleep out 
	vTaskDelay(200/portTICK_PERIOD_MS);
	//************* Start Initial Sequence **********// 
	LCD_WR_REG(0x36);

#if   USE_HORIZONTAL == 0
	LCD_WR_DATA8(0x00);
#elif USE_HORIZONTAL == 1
	LCD_WR_DATA8(0xC0);
#elif USE_HORIZONTAL == 2
	LCD_WR_DATA8(0x70);
#else
	LCD_WR_DATA8(0xA0);
#endif

	LCD_WR_REG(0x3A);
	LCD_WR_DATA8(0x05);

	LCD_WR_REG(0xB2);
	LCD_WR_DATA8(0x0C);
	LCD_WR_DATA8(0x0C);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x33);
	LCD_WR_DATA8(0x33);

	LCD_WR_REG(0xB7);
	LCD_WR_DATA8(0x35);

	LCD_WR_REG(0xBB);
	LCD_WR_DATA8(0x32); //Vcom=1.35V

	LCD_WR_REG(0xC2);
	LCD_WR_DATA8(0x01);

	LCD_WR_REG(0xC3);
	LCD_WR_DATA8(0x15); //GVDD=4.8V  颜色深度

	LCD_WR_REG(0xC4);
	LCD_WR_DATA8(0x20); //VDV, 0x20:0v

	LCD_WR_REG(0xC6);
	LCD_WR_DATA8(0x0F); //0x0F:60Hz

	LCD_WR_REG(0xD0);
	LCD_WR_DATA8(0xA4);
	LCD_WR_DATA8(0xA1);

	LCD_WR_REG(0xE0);
	LCD_WR_DATA8(0xD0);
	LCD_WR_DATA8(0x08);
	LCD_WR_DATA8(0x0E);
	LCD_WR_DATA8(0x09);
	LCD_WR_DATA8(0x09);
	LCD_WR_DATA8(0x05);
	LCD_WR_DATA8(0x31);
	LCD_WR_DATA8(0x33);
	LCD_WR_DATA8(0x48);
	LCD_WR_DATA8(0x17);
	LCD_WR_DATA8(0x14);
	LCD_WR_DATA8(0x15);
	LCD_WR_DATA8(0x31);
	LCD_WR_DATA8(0x34);

	LCD_WR_REG(0xE1);
	LCD_WR_DATA8(0xD0);
	LCD_WR_DATA8(0x08);
	LCD_WR_DATA8(0x0E);
	LCD_WR_DATA8(0x09);
	LCD_WR_DATA8(0x09);
	LCD_WR_DATA8(0x15);
	LCD_WR_DATA8(0x31);
	LCD_WR_DATA8(0x33);
	LCD_WR_DATA8(0x48);
	LCD_WR_DATA8(0x17);
	LCD_WR_DATA8(0x14);
	LCD_WR_DATA8(0x15);
	LCD_WR_DATA8(0x31);
	LCD_WR_DATA8(0x34);
	LCD_WR_REG(0x21);

	LCD_WR_REG(0x29);
}
