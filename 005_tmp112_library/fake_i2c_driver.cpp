#include "fake_i2c_driver.hpp"
#include <iostream>

using namespace std;

namespace
{
FakeTmp112Sensor* sensor {nullptr};
};

void FakeTmp112SensorI2C::init(FakeTmp112Sensor* tmp112)
{
    sensor = tmp112;
}

void FakeTmp112SensorI2C::tx(uint8_t address, uint8_t* data, size_t size)
{
    vector<uint8_t> txBuf;
    txBuf.push_back(static_cast<uint8_t>(address << 1));

    for (int i = 0; i < size; i++)
    {
        txBuf.push_back(data[i]);
    }

    sensor->tx(txBuf);
}

void FakeTmp112SensorI2C::rx(uint8_t address, uint8_t* read_data, size_t size)
{
    vector<uint8_t> txBuf;
    txBuf.push_back(static_cast<uint8_t>(address << 1) | 0x01);
    sensor->tx(txBuf);

    auto rxBytes = sensor->rx();

    auto it = rxBytes.begin();
    for (int i = 0; i < size && it != rxBytes.end(); i++, it++)
    {
        read_data[i] = *it;
    }
}


void FakeTmp112Sensor::tx(vector<uint8_t> txBuffer)
{
    for (const auto& val: txBuffer)
    {
        txBytes.push_back(val);
        interpret(val);
    }
    m_state = States::IDLE;
}


vector<uint8_t> FakeTmp112Sensor::rx()
{
    return rxBytes;
}

void FakeTmp112Sensor::interpret(uint8_t val)
{
    // cout << static_cast<int>(m_state) << ":" << static_cast<unsigned int>(val) << endl;
    switch(m_state)
    {
        case States::IDLE:
            if (val == WRITE)
            {
                m_state = States::GET_POINTER_ADDR;
            }
            else if (val == READ)
            {
                prep_response();
            }
            break;

        case States::GET_POINTER_ADDR:
            m_pointer = val;
            m_state = States::GET_WRITE_VALUE_MSB;
            break;

        case States::GET_WRITE_VALUE_MSB:
            update_registers_msb(val);
            m_state = States::GET_WRITE_VALUE_LSB;
            break;

        case States::GET_WRITE_VALUE_LSB:
            update_registers_lsb(val);
            m_state = States::IDLE;
            break;
    };
}

void FakeTmp112Sensor::update_registers_lsb(uint8_t lsb)
{
    uint16_t lsb16 {lsb};
    m_register_file[m_pointer] = (m_register_file[m_pointer] & 0xFF00) | lsb16;
}

void FakeTmp112Sensor::update_registers_msb(uint8_t msb)
{
    uint16_t msb16 {static_cast<uint16_t>(static_cast<uint16_t>(msb) << 8)};
    m_register_file[m_pointer] = (m_register_file[m_pointer] & 0xFF00) | msb16;
}

void FakeTmp112Sensor::set_temperature(const double temperature)
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

    uint8_t msb {static_cast<uint8_t>(static_cast<uint16_t>(val & 0xFF0) >> 4)};
    uint8_t lsb {static_cast<uint8_t>(static_cast<uint16_t>(val & 0x00F) << 4)};

    rxBytes.push_back(msb);
    rxBytes.push_back(lsb);
}

void FakeTmp112Sensor::set_temperature_extended(const double temperature)
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
        val &= 0x1FFF;
    }

    uint8_t msb {static_cast<uint8_t>(static_cast<uint16_t>(val & 0x1FE0) >> 5)};
    uint8_t lsb {static_cast<uint8_t>(static_cast<uint16_t>(val & 0x001F) << 3)};
    lsb |= 0x01;

    rxBytes.push_back(msb);
    rxBytes.push_back(lsb);
}

void FakeTmp112Sensor::prep_response()
{
    if (m_pointer == 0x00)
    {
        m_lastCommand = "Read temperature";
    }
}

bool FakeTmp112Sensor::is_extended_mode()
{
    // print_reg();
    return m_register_file[1] & 0x0010;
}

void FakeTmp112Sensor::print_reg()
{
    for (const auto& reg: m_register_file)
        cout << "Regs:" << reg << endl;
}
