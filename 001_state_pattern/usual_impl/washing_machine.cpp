#include "washing_machine.hpp"
#include "Ilaundry_sensor.hpp"
#include "Iindicator.hpp"
#include "Iuser_inputs.hpp"
#include "Iwashing_cycles.hpp"
#include "Iwater_sensor.hpp"

WashingMachine::WashingMachine(
        ILaundrySensor& laundrySensor, IIndicator& indicator,
        IUserInputs& userInputs, IWashingCycles& washingCycles, IWaterSensor& waterSensor):
    m_laundrySensor(laundrySensor), m_indicator(indicator), m_userInputs(userInputs),
    m_washCycles(washingCycles), m_waterSensor(waterSensor)
{
}

void WashingMachine::Run()
{
    m_indicator.SetLaundryLevel(Convert(m_laundrySensor.GetLevel()));

    if (m_laundrySensor.GetLevel() != ILaundrySensor::LaundryLevel::NONE)
    {
        m_indicator.SetWaterLevel(IIndicator::WaterLevel::L1);
    }

    if (m_userInputs.HasStartButtonPressed())
    {
        m_washCycles.StartWater();
        m_indicator.SetActualWaterLevel(Convert(m_waterSensor.GetLevel()));
    }
}

IIndicator::LaundryLevel WashingMachine::Convert(ILaundrySensor::LaundryLevel level)
{
    switch (level)
    {
        case ILaundrySensor::LaundryLevel::NONE:
            return IIndicator::LaundryLevel::NONE;
        case ILaundrySensor::LaundryLevel::L1:
            return IIndicator::LaundryLevel::L1;
        case ILaundrySensor::LaundryLevel::L2:
            return IIndicator::LaundryLevel::L2;
    }

    return IIndicator::LaundryLevel::NONE;
}

IIndicator::WaterLevel WashingMachine::Convert(IWaterSensor::WaterLevel level)
{
    switch (level)
    {
        case IWaterSensor::WaterLevel::NONE:
            return IIndicator::WaterLevel::NONE;
        case IWaterSensor::WaterLevel::L1:
            return IIndicator::WaterLevel::L1;
    }

    return IIndicator::WaterLevel::NONE;
}
