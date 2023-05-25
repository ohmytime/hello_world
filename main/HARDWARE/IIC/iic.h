#ifndef _IIC_H_
#define _IIC_H_

#include "sys.h"

#define PIN_NUM_SCL GPIO_NUM_5
#define PIN_NUM_SDA GPIO_NUM_4
#define IIC_NUM     I2C_NUM_0
#define IIC_FREQ    100000
#define IIC_TX_BUF_LEN 0
#define IIC_RX_BUF_LEN 0

#define WRITE_BIT       I2C_MASTER_WRITE    /*!< I2C master write */
#define READ_BIT        I2C_MASTER_READ     /*!< I2C master read */
#define ACK_CHECK_EN    0x1                 /*!< I2C master will check ack from slave*/
#define ACK_CHECK_DIS   0x0                 /*!< I2C master will not check ack from slave */
#define ACK_VAL         0x0                 /*!< I2C ack value */
#define NACK_VAL        0x1                 /*!< I2C nack value */


int IIC_Init(void);
int IIC_Sent(uint8_t slaveAddr, uint8_t *pData, uint16_t dataLen);
int IIC_Read(uint8_t slaveAddr, uint8_t *pData, uint16_t dataLen);

#endif

