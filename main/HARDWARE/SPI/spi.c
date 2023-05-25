#include "spi.h"

static spi_device_handle_t spi;

extern void spi_disp_flush_ready(void);

IRAM_ATTR  void spi_ready(spi_transaction_t *trans)
{
    if ((uint32_t)trans->user == USER_TRANS_STA_OVER) spi_disp_flush_ready();
}

void SPI_Init(void)
{

    spi_bus_config_t buscfg = {
        .miso_io_num=PIN_NUM_MISO,
        .mosi_io_num=PIN_NUM_MOSI,
        .sclk_io_num=PIN_NUM_CLK,
        .quadwp_io_num=-1,
        .quadhd_io_num=-1,
        .max_transfer_sz=4094
    };

    spi_device_interface_config_t devcfg = {
        .clock_speed_hz = SPI_MASTER_FREQ_80M,
        .mode = 0,
        .spics_io_num = PIN_NUM_CS,
        .queue_size = SPI_SENT_QUEUE_NUM,   // SPI消息队列
        .cs_ena_pretrans = 1,
        .post_cb = spi_ready,   //发送完成回调函数
    };
    spi_bus_initialize(SPI2_HOST, &buscfg, SPI_DMA_CH_AUTO);
    spi_bus_add_device(SPI2_HOST, &devcfg, &spi);
}

void SPI_Sent_Byte(const uint8_t data)
{
    esp_err_t ret;
    spi_transaction_t t;
    memset(&t, 0, sizeof(t));
    t.length = 8;
    t.tx_buffer = &data;
    t.user = (void*)0;
    ret = spi_device_polling_transmit(spi, &t);
    assert(ret == ESP_OK);
}

void SPI_Sent_Data(const uint16_t data)
{
    esp_err_t ret;
    spi_transaction_t t;
    memset(&t, 0, sizeof(t));
    t.length = 16;
    t.tx_buffer = &data;
    t.user = (void*)0;
    ret = spi_device_polling_transmit(spi, &t);
    assert(ret == ESP_OK);
}

IRAM_ATTR void SPI_Sent(uint16_t *data, uint32_t len)
{
    spi_transaction_t t;
    memset(&t, 0, sizeof(t));
    t.length = len;
    t.tx_buffer = data;
    t.user = (void *)0;
    esp_err_t ret = spi_device_polling_transmit(spi, &t);
    assert(ret == ESP_OK);
}

IRAM_ATTR void SPI_Sent_Queue(uint16_t *data, uint32_t len, uint32_t user_trans_sta)
{
    static spi_transaction_t t[SPI_SENT_QUEUE_NUM];
    static uint32_t i = 0;

    memset(&t[i], 0, sizeof(spi_transaction_t));
    t[i].length = len;
    t[i].tx_buffer = data;
    t[i].user = (void *)user_trans_sta;
    esp_err_t ret = spi_device_queue_trans(spi, &t[i], portMAX_DELAY);
    assert(ret == ESP_OK);
    if (++i == SPI_SENT_QUEUE_NUM)    i = 0;
}
