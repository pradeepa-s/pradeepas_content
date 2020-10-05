#include "washing_machine.hpp"
#include "Ilaundry_sensor.hpp"
#include "Iindicator.hpp"
#include "Iuser_inputs.hpp"
#include "Iwashing_cycles.hpp"
#include "Iwater_sensor.hpp"
#include "Istate_control.hpp"
#include "idle_state.hpp"
#include "standby_state.hpp"
#include "add_water_state.hpp"
#include "wash_state.hpp"
#include "rinse_state.hpp"
#include "done_state.hpp"
#include "spin_state.hpp"
#include "error_state.hpp"

using namespace std;

WashingMachine::WashingMachine(
        ILaundrySensor& laundrySensor, IIndicator& indicator,
        IUserInputs& userInputs, IWashingCycles& washingCycles, IWaterSensor& waterSensor):
    m_laundrySensor(laundrySensor), m_indicator(indicator), m_userInputs(userInputs),
    m_washCycles(washingCycles), m_waterSensor(waterSensor)
{
    auto idleState = make_shared<IdleState>(*this, m_laundrySensor);
    auto standbyState = make_shared<StandbyState>(*this, m_laundrySensor, m_indicator, m_userInputs);
    auto addWaterState = make_shared<AddWaterState>(*this, m_waterSensor, m_washCycles);
    auto washState = make_shared<WashState>(*this, m_indicator, m_washCycles);
    auto rinseState = make_shared<RinseState>(*this, m_indicator, m_washCycles);
    auto spinState = make_shared<SpinState>(*this, m_washCycles, m_indicator);
    auto doneState = make_shared<DoneState>(*this, m_laundrySensor, m_indicator);
    auto errorState = make_shared<ErrorState>(*this, m_washCycles, m_indicator, m_userInputs);

    m_states.insert(
            make_pair(
                IWashingMachineState::State::IDLE, idleState));
    m_states.insert(
            make_pair(
                IWashingMachineState::State::STANDBY, standbyState));
    m_states.insert(
            make_pair(
                IWashingMachineState::State::ADD_WATER, addWaterState));
    m_states.insert(
            make_pair(
                IWashingMachineState::State::WASH, washState));
    m_states.insert(
            make_pair(
                IWashingMachineState::State::RINSE, rinseState));
    m_states.insert(
            make_pair(
                IWashingMachineState::State::SPIN, spinState));
    m_states.insert(
            make_pair(
                IWashingMachineState::State::DONE, doneState));
    m_states.insert(
            make_pair(
                IWashingMachineState::State::ERROR, errorState));

    m_currentState = m_states[IWashingMachineState::State::IDLE];
}

void WashingMachine::Run()
{
    m_indicator.SetActualWaterLevel(m_waterSensor.GetLevel());
    m_currentState->Run();
}

void WashingMachine::ChangeState(IWashingMachineState::State state)
{
    m_prevStateName = m_currentState->WhoAmI();
    m_currentState = m_states[state];
    m_currentState->Reset();
}

void WashingMachine::Run2()
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
                m_state = WashingMachineState::STARTING_WASH;
            }
            break;

        case WashingMachineState::STARTING_WASH:
            m_washCycles.StartWashAlgorithm();
            m_indicator.SetState(IIndicator::MachineState::WASHING);
            m_state = WashingMachineState::WASH;
            break;

        case WashingMachineState::WASH:
            if (m_washCycles.IsAlgorithmDone())
            {
                m_state = WashingMachineState::STARTING_RINSE;
            }
            break;

        case WashingMachineState::STARTING_RINSE:
            m_washCycles.StartRinseAlgorithm();
            m_indicator.SetState(IIndicator::MachineState::RINSE);
            m_state = WashingMachineState::RINSE;
            break;

        case WashingMachineState::RINSE:
            if (m_washCycles.IsAlgorithmDone())
            {
                m_state = WashingMachineState::STARTING_SPIN;
            }
            break;

        case WashingMachineState::STARTING_SPIN:
            m_washCycles.StartSpinAlgorithm();
            m_indicator.SetState(IIndicator::MachineState::SPIN);
            m_state = WashingMachineState::SPIN;
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
            else if (m_userInputs.HasStopButtonPressed())
            {
                m_washCycles.Reset();
                m_state = WashingMachineState::IDLE;
                m_indicator.SetState(IIndicator::MachineState::IDLE);
            }
            break;

        default:
            break;
    }
}

IWashingMachineState::State WashingMachine::GetPreviousState() const
{
    return m_prevStateName;
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

void WashingMachine::SetWaterLevelTarget(IWaterSensor::WaterLevel level)
{
    m_waterLevelTarget = level;
}

IWaterSensor::WaterLevel WashingMachine::GetWaterLevelTarget() const
{
    return m_waterLevelTarget;
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
        case WashingMachineState::WASH:
            return WashingMachineState::STARTING_WASH;
        case WashingMachineState::RINSE:
            return WashingMachineState::STARTING_RINSE;
        case WashingMachineState::SPIN:
            return WashingMachineState::STARTING_SPIN;
        default:
            return state;
    }
}
