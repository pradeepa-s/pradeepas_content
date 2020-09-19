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
    m_indicator.SetActualWaterLevel(Convert(m_waterSensor.GetLevel()));

    if (m_state != WashingMachineState::ERROR && m_washCycles.IsInError())
    {
        m_preErrorState = m_state;
        m_state = WashingMachineState::ERROR;
    }

    switch (m_state)
    {
        case WashingMachineState::IDLE:
            if (m_laundrySensor.GetLevel() != ILaundrySensor::LaundryLevel::NONE)
            {
                m_state = WashingMachineState::STANDBY;
            }
            break;

        case WashingMachineState::STANDBY:
            m_indicator.SetLaundryLevel(Convert(m_laundrySensor.GetLevel()));
            m_recommendedWaterLevel = GetRecommendedWaterLevel(m_laundrySensor.GetLevel());
            m_indicator.SetRecommendedWaterLevel(Convert(m_recommendedWaterLevel));

            if (m_userInputs.HasStartButtonPressed())
            {
                m_state = WashingMachineState::STARTING_WATER;
            }
            break;

        case WashingMachineState::STARTING_WATER:
            m_washCycles.StartWater();
            m_state = WashingMachineState::ADD_WATER;
            break;

        case WashingMachineState::ADD_WATER:
            if (RecommendedWaterLevelReached())
            {
                m_washCycles.StopWater();
                m_washCycles.StartWashAlgorithm();
                m_indicator.SetState(IIndicator::MachineState::WASHING);
                m_state = WashingMachineState::WASH;
            }
            break;

        case WashingMachineState::WASH:
            if (m_washCycles.IsAlgorithmDone())
            {
                m_washCycles.StartRinseAlgorithm();
                m_indicator.SetState(IIndicator::MachineState::RINSE);
                m_state = WashingMachineState::RINSE;
            }
            break;

        case WashingMachineState::RINSE:
            if (m_washCycles.IsAlgorithmDone())
            {
                m_washCycles.StartSpinAlgorithm();
                m_indicator.SetState(IIndicator::MachineState::SPIN);
                m_state = WashingMachineState::SPIN;
            }
            break;

        case WashingMachineState::SPIN:
            if (m_washCycles.IsAlgorithmDone())
            {
                m_washCycles.StopSpinAlgorithm();
                m_indicator.SetState(IIndicator::MachineState::DONE);
                m_state = WashingMachineState::DONE;
            }
            break;

        case WashingMachineState::DONE:
            if (m_laundrySensor.GetLevel() == ILaundrySensor::LaundryLevel::NONE)
            {
                m_indicator.SetLaundryLevel(Convert(m_laundrySensor.GetLevel()));
                m_indicator.SetRecommendedWaterLevel(IIndicator::WaterLevel::NONE);
                m_state = WashingMachineState::IDLE;
            }
            break;

        case WashingMachineState::ERROR:
            m_indicator.SetState(IIndicator::MachineState::ERROR);
            if (m_userInputs.HasStartButtonPressed())
            {
                m_washCycles.ClearError();
                m_state = GetPreErrorState(m_preErrorState);
            }
            break;

        default:
            break;
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

bool WashingMachine::RecommendedWaterLevelReached()
{
    return m_recommendedWaterLevel == m_waterSensor.GetLevel();
}

WashingMachine::WashingMachineState WashingMachine::GetPreErrorState(WashingMachineState state)
{
    switch (state)
    {
        case WashingMachineState::ADD_WATER:
            return WashingMachineState::STARTING_WATER;
        default:
            return state;
    }
}
