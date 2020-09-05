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
    IWaterSensor::WaterLevel recommendedWaterLevel = GetRecommendedWaterLevel(
            m_laundrySensor.GetLevel());

    m_indicator.SetWaterLevel(Convert(recommendedWaterLevel));

    if (!m_started && m_userInputs.HasStartButtonPressed())
    {
        m_washCycles.StartWater();
        m_started = true;
    }
    else
    {
        m_indicator.SetActualWaterLevel(Convert(m_waterSensor.GetLevel()));

        if (!m_washStarted && m_waterSensor.GetLevel() == recommendedWaterLevel)
        {
            m_washCycles.StopWater();
            m_washCycles.StartWashAlgorithm();
            m_washStarted = true;
        }
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
        case IWaterSensor::WaterLevel::L2:
            return IIndicator::WaterLevel::L2;
    }

    return IIndicator::WaterLevel::NONE;
}

IWaterSensor::WaterLevel WashingMachine::GetRecommendedWaterLevel(ILaundrySensor::LaundryLevel level)
{
    switch (level)
    {
        case ILaundrySensor::LaundryLevel::NONE:
            return IWaterSensor::WaterLevel::NONE;
        case ILaundrySensor::LaundryLevel::L1:
            return IWaterSensor::WaterLevel::L1;
        case ILaundrySensor::LaundryLevel::L2:
            return IWaterSensor::WaterLevel::L2;
    }

    return IWaterSensor::WaterLevel::NONE;
}
