#ifndef TMP112_SENSOR
#define TMP112_SENSOR

#include <stdint.h>
#include <stddef.h>

typedef void (*tmp112_tx_func)(uint8_t address, uint8_t* data, size_t size);
typedef void (*tmp112_rx_func)(uint8_t address, uint8_t* read_data, size_t size);

enum _TMP112_CONVERSION_RATE { HZ_0_25=0, HZ_1=0x40, HZ_4=0x80, HZ_8=0xC0 };

typedef enum _TMP112_CONVERSION_RATE TMP112_CONVERSION_RATE;

typedef struct _TMP112_CONFIG {
    TMP112_CONVERSION_RATE conversion_rate;
    uint8_t thermostat_mode;
    uint8_t alert_polartiy;
    uint8_t fault_queue;
    uint8_t extended_mode;
} TMP112_CONFIG;

#define TMP112_EXTENDED_MODE_ENABLED (0x10)

void tmp112_sensor_init(uint8_t slave_address, tmp112_tx_func tx, tmp112_rx_func rx);
void tmp112_sensor_deinit();
double tmp112_sensor_get_temperature();
double tmp112_sensor_get_temperature_ex();
void tmp112_sensor_set_config(TMP112_CONFIG config);
void tmp112_sensor_shutdown(uint8_t enable);

#endif //  TMP112_SENSOR
