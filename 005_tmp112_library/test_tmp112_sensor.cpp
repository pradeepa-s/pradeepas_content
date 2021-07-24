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
        FakeTmp112SensorI2C::init(&fakeSensor);
        tmp112_sensor_init(SLAVE_ADDRESS, FakeTmp112SensorI2C::tx, FakeTmp112SensorI2C::rx);
    }

    ~TestTmp112Sensor()
    {
        tmp112_sensor_deinit();
    }

    void IsLastI2CTransactionReadTemperature()
    {
        EXPECT_EQ(fakeSensor.m_lastCommand, "Read temperature");
    }

    void IsLastI2CTransactionSetExtendedMode()
    {
        EXPECT_TRUE(fakeSensor.is_extended_mode());
    }

    void IsLastI2CTransactionAddressedTo(const uint8_t address)
    {
         uint8_t slaveAddr = (fakeSensor.txBytes[0] >> 1) & 0x7F;
         EXPECT_EQ(address, slaveAddr);
    }

    void SetNextTemperatureReading(const double nextReadingInCentigrades)
    {
        fakeSensor.set_temperature(nextReadingInCentigrades);
    }

    void SetNextTemperatureReadingInExtendedMode(const double nextReadingInCentigrades)
    {
        fakeSensor.set_temperature_extended(nextReadingInCentigrades);
    }

    static constexpr uint8_t SLAVE_ADDRESS {0x48};
    static constexpr uint8_t SLAVE_ADDRESS_2 {0x11};

    static constexpr uint8_t WRITE_ADDRESS {SLAVE_ADDRESS << 1};
    static constexpr uint8_t READ_ADDRESS {SLAVE_ADDRESS << 1 | 0x01};

    FakeTmp112Sensor fakeSensor {};
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

TEST_F(TestTmp112Sensor, get_temperature_returns_negative_value_in_centigrades)
{
    SetNextTemperatureReading(-40.875);
    EXPECT_EQ(-40.875, tmp112_sensor_get_temperature());
}

TEST_F(TestTmp112Sensor, shall_set_extended_mode)
{
    tmp112_sensor_set_extended_mode(1);
    IsLastI2CTransactionSetExtendedMode();
}

TEST_F(TestTmp112Sensor, get_temperature_ex_returns_value_in_centigrades_in_extended_mode)
{
    SetNextTemperatureReadingInExtendedMode(149.9375);
    tmp112_sensor_set_extended_mode(1);
    EXPECT_EQ(149.9375, tmp112_sensor_get_temperature_ex());
}

TEST_F(TestTmp112Sensor, get_temperature_ex_returns_negative_value_in_centigrades_in_extended_mode)
{
    SetNextTemperatureReadingInExtendedMode(-55);
    tmp112_sensor_set_extended_mode(1);
    EXPECT_EQ(-55, tmp112_sensor_get_temperature_ex());
}
