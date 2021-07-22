#include "fake_i2c_driver.hpp"

using namespace std;

vector<uint8_t> FakeTmp112SensorI2C::txBytes{};
namespace
{
vector<uint8_t> rxBytes {};
};

void FakeTmp112SensorI2C::init()
{
    FakeTmp112SensorI2C::txBytes.clear();
    rxBytes.clear();
}

void FakeTmp112SensorI2C::tx(uint8_t address, uint8_t* data, size_t size)
{
    FakeTmp112SensorI2C::txBytes.push_back(static_cast<uint8_t>(address << 1));

    for (int i = 0; i < size; i++)
    {
        FakeTmp112SensorI2C::txBytes.push_back(data[i]);
    }
}

void FakeTmp112SensorI2C::rx(uint8_t address, uint8_t* read_data, size_t size)
{
    FakeTmp112SensorI2C::txBytes.push_back(static_cast<uint8_t>((address << 1) | 0x01));

    auto it = rxBytes.begin();
    for (int i = 0; i < size && it != rxBytes.end(); i++, it++)
    {
        read_data[i] = *it;
    }
}

void FakeTmp112SensorI2C::set_next_temp_reading(const double temperature)
{
    uint32_t val {0};
    if (temperature >= 0)
    {
        val = temperature / 0.0625;
    }
    else
    {
        const int32_t binaryCode {static_cast<int32_t>(temperature / 0.0625 )};
        val = static_cast<uint32_t>(binaryCode);
        val &= 0xFFF;
    }

    rxBytes.push_back(val & 0xFF);
    rxBytes.push_back((val >> 8) & 0xFF);
}
