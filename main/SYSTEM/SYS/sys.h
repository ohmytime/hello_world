#ifndef _SYS_H_
#define _SYS_H_

#include <stdio.h>
#include "stdlib.h"
#include "string.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "esp_log.h"
#include "sdkconfig.h"

#include "driver/gpio.h"
#include "driver/spi_master.h"
#include "driver/i2c.h"
#include "driver/timer.h"

typedef unsigned char   u8;
typedef unsigned short  u16;
typedef unsigned int    u32;

#define True    1
#define False   0
#define ENABLE  1
#define DISABLE 0

#define GPIO_LEVEL_HIGH 1
#define GPIO_LEVEL_LOW  0

#endif