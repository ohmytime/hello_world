#ifndef _SPI_H_
#define _SPI_H_

#include "sys.h"

#define DMA_CHAN    2

#define PIN_NUM_MISO -1
#define PIN_NUM_MOSI 3
#define PIN_NUM_CLK  2
#define PIN_NUM_CS   7

#define SPI_SENT_QUEUE_NUM      30
#define USER_TRANS_STA_CONTINUE 0x00
#define USER_TRANS_STA_OVER     0x01

void SPI_Init(void);
void SPI_Sent(uint16_t *dat,uint32_t len);
void SPI_Sent_Byte(const uint8_t data);
void SPI_Sent_Data(const uint16_t data);
IRAM_ATTR void SPI_Sent_Queue(uint16_t *dat,uint32_t len,uint32_t user_fg);

#endif
