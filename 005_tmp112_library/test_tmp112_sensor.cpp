#include <gtest/gtest.h>
extern "C" {
#include "tmp112_sensor.h"
}
#include "fake_i2c_driver.hpp"
#include <vector>

using namespace std;

class TestTmp112Sensor: public ::testing::Test
{
protected:
    TestTmp112Sensor()
    {
        FakeTmp112SensorI2C::init();
        tmp112_sensor_init(SLAVE_ADDRESS, FakeTmp112SensorI2C::tx, FakeTmp112SensorI2C::rx);
    }

    ~TestTmp112Sensor()
    {
        tmp112_sensor_deinit();
    }

    void IsLastI2CTransactionReadTemperature()
    {
        constexpr uint8_t WRITE {0b10010000};
        constexpr uint8_t READ {0b10010001};

        // Send device address with write condition
        // Write pointer register
        // Send device address and with read bit set
        vector<uint8_t> exp{WRITE, 0x00, READ};

        EXPECT_EQ(exp, FakeTmp112SensorI2C::txBytes);
    }

    void IsLastI2CTransactionAddressedTo(const uint8_t address)
    {
        uint8_t slaveAddr = (FakeTmp112SensorI2C::txBytes[0] >> 1) & 0x7F;
        EXPECT_EQ(address, slaveAddr);
    }

    void SetNextTemperatureReading(const double nextReadingInCentigrades)
    {
        FakeTmp112SensorI2C::set_next_temp_reading(nextReadingInCentigrades);
    }

    static constexpr uint8_t SLAVE_ADDRESS {0x48};
    static constexpr uint8_t SLAVE_ADDRESS_2 {0x11};
};


TEST_F(TestTmp112Sensor, shall_be_able_to_set_the_slave_address)
{
    tmp112_sensor_init(SLAVE_ADDRESS_2, FakeTmp112SensorI2C::tx, FakeTmp112SensorI2C::rx);
    tmp112_sensor_get_temperature();
    IsLastI2CTransactionAddressedTo(SLAVE_ADDRESS_2);
}

TEST_F(TestTmp112Sensor, get_temperature_reads_correct_register_over_i2c)
{
    tmp112_sensor_get_temperature();
    IsLastI2CTransactionReadTemperature();
}

TEST_F(TestTmp112Sensor, get_temperature_returns_value_in_centigrades)
{
    SetNextTemperatureReading(31.1875);
    EXPECT_EQ(31.1875, tmp112_sensor_get_temperature());
}

TEST_F(TestTmp112Sensor, get_temperature_returns_negetive_value_in_centigrades)
{
    SetNextTemperatureReading(-40.875);
    EXPECT_EQ(-40.875, tmp112_sensor_get_temperature());
}
