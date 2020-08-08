#include "washing_machine.hpp"
#include "laundry_sensor.hpp"
#include "indicator.hpp"

WashingMachine::WashingMachine(LaundrySensor& laundrySensor, Indicator& indicator):
    m_laundrySensor(laundrySensor), m_indicator(indicator)
{
}

void WashingMachine::Run()
{
    m_indicator.SetLaundryLevel(m_laundrySensor.GetLevel());

    if (m_laundrySensor.GetLevel() != LaundrySensor::LaundryLevel::NONE)
    {
        m_indicator.SetWaterLevel(Indicator::WaterLevel::L1);
    }
}
