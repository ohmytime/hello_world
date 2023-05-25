#ifndef _TOUCH_H_
#define _TOUCH_H_

#include "iic.h"

#define TP_PRES_DOWN 0x80  //触屏被按下	
#define TP_COORD_UD  0x40  //触摸坐标更新标记

//触摸点相关数据结构体定义
typedef  struct
{
	uint8_t TouchInt;	//触摸中断触发标志
	uint8_t TouchSta;	//触摸情况，b7:按下1/松开0; b6:0没有按键按下/1有按键按下;bit5:保留；bit4-bit0触摸点按下有效标志，有效为1，分别对应触摸点5-1；
	uint16_t x[5];		//支持5点触摸，需要使用5组坐标存储触摸点数据
	uint16_t y[5];
}	TouchPointRefTypeDef;

extern TouchPointRefTypeDef TPR_Structure;

//I2C读写命令	
#define FT_CMD_WR 				0X70    	//写命令
#define FT_CMD_RD 				0X71		//读命令
//FT6236 部分寄存器定义 
#define FT_DEVIDE_MODE 			0x00   		//FT6236模式控制寄存器
#define FT_REG_NUM_FINGER       0x02		//触摸状态寄存器

#define FT_TP1_REG 				0X03	  	//第一个触摸点数据地址
#define FT_TP2_REG 				0X09		//第二个触摸点数据地址
#define FT_TP3_REG 				0X0F		//第三个触摸点数据地址
#define FT_TP4_REG 				0X15		//第四个触摸点数据地址
#define FT_TP5_REG 				0X1B		//第五个触摸点数据地址  


#define	FT_ID_G_LIB_VERSION		0xA1		//版本		
#define FT_ID_G_MODE 			0xA4   		//FT6236中断模式控制寄存器
#define FT_ID_G_THGROUP			0x80   		//触摸有效值设置寄存器
#define FT_ID_G_PERIODACTIVE	0x88   		//激活状态周期设置寄存器  
#define Chip_Vendor_ID          0xA3        //芯片ID(0x36)
#define ID_G_FT6236ID			0xA8		//0x11


#define PIN_TOUCH_NUM_RES   GPIO_NUM_8
#define PIN_TOUCH_NUM_INT   GPIO_NUM_9

#define TOUCH_RES_Clr()		gpio_set_level(PIN_TOUCH_NUM_RES, GPIO_LEVEL_LOW)//RES
#define TOUCH_RES_Set()		gpio_set_level(PIN_TOUCH_NUM_RES, GPIO_LEVEL_HIGH)

void TOUCH_Scan(void);
void TOUCH_Init(void);

#endif

