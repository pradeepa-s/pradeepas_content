#include "tmp112_sensor.h"
#include <string.h>
#include <stdio.h>


static double transform_to_centigrades(uint8_t* register_data);
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

double transform_to_centigrades(uint8_t* register_data)
{
    uint16_t binary_data = 0;
    memcpy(&binary_data, register_data, 2);

    int32_t val_before_resolution = binary_data;
    if (binary_data & 0x800)
    {
        binary_data = ((~binary_data) & 0xFFF) + 1;
        val_before_resolution = -1 * binary_data;
    }
    double temp = val_before_resolution * 0.0625;
    return temp;
}
