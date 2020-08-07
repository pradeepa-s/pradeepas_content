#include "washing_machine.hpp"
#include "laundry_sensor.hpp"
#include "indicator.hpp"

WashingMachine::WashingMachine(LaundrySensor& laundrySensor, Indicator& indicator):
    m_laundrySensor(laundrySensor), m_indicator(indicator)
{
}

void WashingMachine::Run()
{
    if(m_laundrySensor.IsAvailable())
    {
        m_indicator.Set(true);
    }
}
