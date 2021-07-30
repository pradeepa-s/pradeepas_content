#ifndef FAKE_I2C_SENSOR
#define FAKE_I2C_SENSOR

#include <cstdint>
#include <vector>
#include <array>
#include <string>

class FakeTmp112Sensor
{
public:
    void tx(std::vector<uint8_t> tx);
    std::vector<uint8_t> rx();
    void set_temperature(const double temperature);
    void set_temperature_extended(const double temperature);
    bool is_extended_mode();
    double get_converstion_rate();
    bool is_shutdown();

    void interpret(uint8_t val);
    void prep_response();
    void update_register(uint8_t reg, uint8_t msb, uint8_t lsb);
    void update_register_lsb(uint8_t reg, uint8_t lsb);
    void update_register_msb(uint8_t reg, uint8_t msb);
    void update_pointed_register_msb(uint8_t val);
    void update_pointed_register_lsb(uint8_t val);
    void print_reg();

    std::vector<uint8_t> txBytes {};
    std::vector<uint8_t> rxBytes {};

    enum class States
    {
        IDLE,
        GET_POINTER_ADDR,
        GET_WRITE_VALUE_MSB,
        GET_WRITE_VALUE_LSB
    };

    States m_state {States::IDLE};
    uint8_t m_pointer {};

    static constexpr uint8_t WRITE {0x90};
    static constexpr uint8_t READ {0x91};

    std::array<uint16_t, 4> m_register_file {};

    std::string m_lastCommand;
};

namespace FakeTmp112SensorI2C
{
    void init(FakeTmp112Sensor* sensor);
    void tx(uint8_t address, uint8_t* data, size_t size);
    void rx(uint8_t address, uint8_t* read_data, size_t size);

};

#endif //  FAKE_I2C_SENSOR
