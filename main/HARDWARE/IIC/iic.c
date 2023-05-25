#include "iic.h"

int IIC_Init(void)
{
	int i2c_master_port = IIC_NUM;
	i2c_config_t conf = {
	    .mode = I2C_MODE_MASTER,
	    .sda_io_num = PIN_NUM_SDA,         // select GPIO specific to your project
	    .sda_pullup_en = GPIO_PULLUP_ENABLE,
	    .scl_io_num = PIN_NUM_SCL,         // select GPIO specific to your project
	    .scl_pullup_en = GPIO_PULLUP_ENABLE,
	    .master.clk_speed = IIC_FREQ,  // select frequency specific to your project
	    // .clk_flags = 0,          /*!< Optional, you can use I2C_SCLK_SRC_FLAG_* flags to choose i2c source clock here. */
	};
    i2c_param_config(i2c_master_port, &conf);
    return i2c_driver_install(i2c_master_port, conf.mode, IIC_RX_BUF_LEN, IIC_TX_BUF_LEN, 0);
}


int IIC_Sent(uint8_t slaveAddr, uint8_t *pData, uint16_t dataLen)
{
    int ret;
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, slaveAddr, ACK_CHECK_EN);
    
    i2c_master_write(cmd, pData, dataLen, ACK_CHECK_EN);
    i2c_master_stop(cmd);
    ret = i2c_master_cmd_begin(IIC_NUM, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
    return ret;
}

int IIC_Read(uint8_t slaveAddr, uint8_t *pData, uint16_t dataLen)
{
    if (dataLen == 0)   return ESP_OK;

    int ret;
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, slaveAddr, ACK_CHECK_EN);

    if (dataLen > 1)   i2c_master_read(cmd, pData, dataLen - 1, ACK_VAL);
    i2c_master_read_byte(cmd, pData + dataLen - 1, NACK_VAL);

    i2c_master_stop(cmd);
    ret = i2c_master_cmd_begin(IIC_NUM, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
    return ret;
}

