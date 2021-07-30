#include "tmp112_sensor.h"
#include <string.h>


static double transform_to_centigrades(uint8_t* register_data);
static double transform_to_centigrades_ex(uint8_t* register_data);
static double get_rate_register(uint8_t* register_data);
static tmp112_tx_func i2c_tx = 0;
static tmp112_rx_func i2c_rx = 0;
static uint8_t slave_address = 0;


void tmp112_sensor_init(uint8_t slave_addr, tmp112_tx_func tx, tmp112_rx_func rx)
{
    i2c_tx = tx;
    i2c_rx = rx;
    slave_address = slave_addr;
}

void tmp112_sensor_deinit()
{
    i2c_tx = 0;
    i2c_rx = 0;
    slave_address = 0;
}

double tmp112_sensor_get_temperature()
{
    uint8_t write_data = 0x00;
    i2c_tx(slave_address, &write_data, 1);

    uint8_t read_data[2];
    i2c_rx(slave_address, read_data, 2);

    return transform_to_centigrades(read_data);
}

double tmp112_sensor_get_temperature_ex()
{
    uint8_t write_data = 0x00;
    i2c_tx(slave_address, &write_data, 1);

    uint8_t read_data[2];
    i2c_rx(slave_address, read_data, 2);

    return transform_to_centigrades_ex(read_data);
}

void tmp112_sensor_set_conversion_rate(TMP112_CONVERSION_RATE rate)
{
    uint8_t reg_val = 0;
    if (rate == HZ_1)
    {
        reg_val = 0x40;
    }
    else if (rate == HZ_4)
    {
        reg_val = 0x80;
    }
    else if (rate == HZ_8)
    {
        reg_val = 0xC0;
    }

    uint8_t write_data = 0x01;
    i2c_tx(slave_address, &write_data, 1);

    uint8_t read_data[2];
    i2c_rx(slave_address, read_data, 2);

    uint8_t update_write[3];
    update_write[0] = 0x01;
    update_write[1] = read_data[0];
    update_write[2] = (read_data[1] & 0x3F) | reg_val;
    i2c_tx(slave_address, update_write, 3);
}

void tmp112_sensor_set_extended_mode(uint8_t enable)
{
    uint8_t write_data = 0x01;
    i2c_tx(slave_address, &write_data, 1);

    uint8_t read_data[2];
    i2c_rx(slave_address, read_data, 2);

    uint8_t update_write[3];
    update_write[0] = 0x01;
    update_write[1] = read_data[0];
    update_write[2] = (read_data[1] & 0xEF) | (enable << 4);
    i2c_tx(slave_address, update_write, 3);
}

void tmp112_sensor_shutdown(uint8_t enable)
{
    uint8_t write_data = 0x01;
    i2c_tx(slave_address, &write_data, 1);

    uint8_t read_data[2];
    i2c_rx(slave_address, read_data, 2);

    uint8_t update_write[3];
    update_write[0] = 0x01;
    update_write[1] = (read_data[0] & 0xFE) | (enable << 0);
    update_write[2] = read_data[1];
    i2c_tx(slave_address, update_write, 3);
}

double transform_to_centigrades(uint8_t* register_data)
{
    const uint16_t msb = register_data[0] << 4;
    const uint16_t lsb = register_data[1] >> 4;

    uint16_t temperature_word = (msb & 0x0FF0) | (lsb & 0x000F) ;
    int32_t val_before_resolution = temperature_word;

    if (temperature_word & 0x800)
    {
    	temperature_word = ((~temperature_word) & 0xFFF) + 1;
        val_before_resolution = -1 * temperature_word;
    }
    return val_before_resolution * 0.0625;
}

double transform_to_centigrades_ex(uint8_t* register_data)
{
    const uint16_t msb = register_data[0] << 5;
    const uint16_t lsb = register_data[1] >> 3;

    uint16_t temperature_word = (msb & 0x1FE0) | (lsb & 0x001F) ;
    int32_t val_before_resolution = temperature_word;

    if (temperature_word & 0x1000)
    {
    	temperature_word = ((~temperature_word) & 0x1FFF) + 1;
        val_before_resolution = -1 * temperature_word;
    }
    return val_before_resolution * 0.0625;
}
