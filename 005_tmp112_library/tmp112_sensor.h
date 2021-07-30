#ifndef TMP112_SENSOR
#define TMP112_SENSOR

#include <stdint.h>
#include <stddef.h>

typedef void (*tmp112_tx_func)(uint8_t address, uint8_t* data, size_t size);
typedef void (*tmp112_rx_func)(uint8_t address, uint8_t* read_data, size_t size);

enum _TMP112_CONVERSION_RATE { HZ_0_25, HZ_1, HZ_4, HZ_8 };

typedef enum _TMP112_CONVERSION_RATE TMP112_CONVERSION_RATE;

void tmp112_sensor_init(uint8_t slave_address, tmp112_tx_func tx, tmp112_rx_func rx);
void tmp112_sensor_deinit();
double tmp112_sensor_get_temperature();
double tmp112_sensor_get_temperature_ex();
void tmp112_sensor_set_extended_mode(uint8_t enable);
void tmp112_sensor_set_conversion_rate(TMP112_CONVERSION_RATE rate);
void tmp112_sensor_shutdown(uint8_t enable);

#endif //  TMP112_SENSOR
