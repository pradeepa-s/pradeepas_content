#include "washing_machine.hpp"
#include "laundry_sensor.hpp"
#include "indicator.hpp"
#include "user_inputs.hpp"
#include "washing_cycles.hpp"

WashingMachine::WashingMachine(
        LaundrySensor& laundrySensor, Indicator& indicator,
        UserInputs& userInputs, WashingCycles& washingCycles):
    m_laundrySensor(laundrySensor), m_indicator(indicator), m_userInputs(userInputs),
    m_washCycles(washingCycles)
{
}

void WashingMachine::Run()
{
    m_indicator.SetLaundryLevel(m_laundrySensor.GetLevel());

    if (m_laundrySensor.GetLevel() != LaundrySensor::LaundryLevel::NONE)
    {
        m_indicator.SetWaterLevel(Indicator::WaterLevel::L1);
    }

    if (m_userInputs.HasStartButtonPressed())
    {
        m_washCycles.StartWater();
    }
}
