#include "touch.h"

uint8_t initbuf1[2]={FT_DEVIDE_MODE,0};
uint8_t initbuf2[2]={FT_ID_G_THGROUP,22};
uint8_t initbuf3[2]={FT_ID_G_PERIODACTIVE,12};

TouchPointRefTypeDef TPR_Structure; 

static void IRAM_ATTR TOUCH_INT_Handler(void *arg)
{
	//连续触摸发送中断信号最短间隔约为9.5ms
	TPR_Structure.TouchInt = true;
}

void TOUCH_GPIO_Init(void)
{
	gpio_reset_pin(PIN_TOUCH_NUM_RES);
	gpio_set_direction(PIN_TOUCH_NUM_RES, GPIO_MODE_OUTPUT);
    gpio_set_level(PIN_TOUCH_NUM_RES,  GPIO_LEVEL_LOW);
}

void INT_Init(void)
{
	gpio_config_t EXTI_config;

    EXTI_config.pin_bit_mask = 1ULL<<PIN_TOUCH_NUM_INT;
    EXTI_config.mode = GPIO_MODE_INPUT;			//输入模式
    EXTI_config.pull_up_en = 1;					//使能上拉
    EXTI_config.pull_down_en = 0;
    EXTI_config.intr_type=GPIO_INTR_NEGEDGE;	//下降沿触发

	gpio_config(&EXTI_config);

	gpio_install_isr_service(ESP_INTR_FLAG_LEVEL3);

	gpio_isr_handler_add(PIN_TOUCH_NUM_INT,TOUCH_INT_Handler,NULL);	//注册中断处理函数
}

void TOUCH_WR_Reg(uint8_t *buf)
{
	IIC_Sent(0X70, buf, sizeof(buf));
}

void TOUCH_RD_Reg(uint16_t reg,uint8_t *buf,uint8_t len)
{
	IIC_Sent(0X70, &reg, 1);
    IIC_Read(0x71, buf, len);
}

void TOUCH_Init(void)
{
	TOUCH_GPIO_Init();
	INT_Init();
    
    vTaskDelay(100/portTICK_PERIOD_MS);
	TOUCH_RES_Clr();
	vTaskDelay(50/portTICK_PERIOD_MS);
	TOUCH_RES_Set();
	vTaskDelay(100/portTICK_PERIOD_MS);

	TOUCH_WR_Reg(initbuf1);
	vTaskDelay(5/portTICK_PERIOD_MS);
	TOUCH_WR_Reg(initbuf2);
	vTaskDelay(5/portTICK_PERIOD_MS);
	TOUCH_WR_Reg(initbuf3);
	vTaskDelay(5/portTICK_PERIOD_MS);
}

const uint16_t TOUCH_TPX_TBL[5] = {
	FT_TP1_REG,
	FT_TP2_REG,
	FT_TP3_REG,
	FT_TP4_REG,
	FT_TP5_REG
};

void TOUCH_Scan(void)
{
	uint8_t i = 0;
	static uint8_t sta = 0;
	static uint8_t buf[4] = {0};

	TOUCH_RD_Reg(0x02, &sta, 1);

 	if(sta & 0x0f)	//判断是否有触摸点按下，0x02寄存器的低4位表示有效触点个数
 	{
 		TPR_Structure.TouchSta = ~(0xFF << (sta & 0x0F));
 		for(i = 0; i < 5; i++)
 		{
 			if(TPR_Structure.TouchSta & (1<<i))	//读取触摸点坐标
 			{
				TOUCH_RD_Reg(TOUCH_TPX_TBL[i], buf, 4);
				
				TPR_Structure.x[i] = ((u16)(buf[0] & 0X0F) << 8) + buf[1];
				TPR_Structure.y[i] = ((u16)(buf[2] & 0X0F) << 8) + buf[3];
 				if((buf[0] & 0XC0) != 0X80)//必须是contact事件，才认为有效
 				{
					TPR_Structure.x[i] = 0;
					TPR_Structure.y[i] = 0;
					return;
				}
 			}
 		}
 		TPR_Structure.TouchSta |= TP_PRES_DOWN;     //触摸按下标记
 	}
 	else
 	{
 		if(TPR_Structure.TouchSta & TP_PRES_DOWN) 	//之前是被按下的
 			TPR_Structure.TouchSta &= ~0x80;        //触摸松开标记	
 		else
 		{
 			TPR_Structure.x[0] = 0;
 			TPR_Structure.y[0] = 0;
 			TPR_Structure.TouchSta &= 0xe0;	//清除触摸点有效标记
 		}
 	} 
}






