#ifndef FAKE_I2C_SENSOR
#define FAKE_I2C_SENSOR

#include <cstdint>
#include <vector>

namespace FakeTmp112SensorI2C
{
    void init();
    void tx(uint8_t address, uint8_t* data, size_t size);
    void rx(uint8_t address, uint8_t* read_data, size_t size);
    void set_next_temp_reading(const double temperature);

    extern std::vector<uint8_t> txBytes;
};

#endif //  FAKE_I2C_SENSOR
