#include "tmp112_sensor.h"


static double transform_to_centigrades(uint8_t* register_data);
static double transform_to_centigrades_ex(uint8_t* register_data);
static double get_rate_register(uint8_t* register_data);
void update_conf_register(uint8_t msb_mask, uint8_t msb_val, uint8_t lsb_mask, uint8_t lsb_val);

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

void tmp112_sensor_set_config(TMP112_CONFIG config)
{
    uint8_t msb_val = 0;
    uint8_t lsb_val = 0;

    /* lsb_val = config.conversion_rate | config.thermostat_mode | config.alert_polartiy | config.fault_queue | config.extended_mode; */
    lsb_val = config.conversion_rate | config.extended_mode;
    update_conf_register(0xff, msb_val, 0xD0, lsb_val);
}

void tmp112_sensor_shutdown(uint8_t enable)
{
    update_conf_register(0x01, (enable << 0), 0x00, 0x00);
}

void update_conf_register(uint8_t msb_mask, uint8_t msb_val, uint8_t lsb_mask, uint8_t lsb_val)
{
    uint8_t write_data = 0x01;
    i2c_tx(slave_address, &write_data, 1);

    uint8_t read_data[2];
    i2c_rx(slave_address, read_data, 2);

    uint8_t update_write[3];
    update_write[0] = 0x01;
    update_write[1] = (read_data[0] & ~msb_mask) | (msb_val & msb_mask);
    update_write[2] = (read_data[1] & ~lsb_mask) | (lsb_val & lsb_mask);
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
