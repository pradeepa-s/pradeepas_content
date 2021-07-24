#ifndef TMP112_SENSOR
#define TMP112_SENSOR

#include <stdint.h>
#include <stddef.h>

typedef void (*tmp112_tx_func)(uint8_t address, uint8_t* data, size_t size);
typedef void (*tmp112_rx_func)(uint8_t address, uint8_t* read_data, size_t size);

void tmp112_sensor_init(uint8_t slave_address, tmp112_tx_func tx, tmp112_rx_func rx);
void tmp112_sensor_deinit();
double tmp112_sensor_get_temperature();
double tmp112_sensor_get_temperature_ex();
void tmp112_sensor_set_extended_mode(uint8_t enable);

#endif //  TMP112_SENSOR
