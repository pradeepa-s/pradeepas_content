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
    m_washCycles(washingCycles), m_waterSensor(waterSensor), m_currentState {nullptr},
    m_prevStateName {StateName::IDLE}, m_waterLevelTarget {IWaterSensor::WaterLevel::L2}
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
                StateName::IDLE, idleState));
    m_states.insert(
            make_pair(
                StateName::STANDBY, standbyState));
    m_states.insert(
            make_pair(
                StateName::ADD_WATER, addWaterState));
    m_states.insert(
            make_pair(
                StateName::WASH, washState));
    m_states.insert(
            make_pair(
                StateName::RINSE, rinseState));
    m_states.insert(
            make_pair(
                StateName::SPIN, spinState));
    m_states.insert(
            make_pair(
                StateName::DONE, doneState));
    m_states.insert(
            make_pair(
                StateName::ERROR, errorState));

    m_currentState = m_states[StateName::IDLE];
}

void WashingMachine::Run()
{
    m_indicator.SetActualWaterLevel(m_waterSensor.GetLevel());
    m_currentState->Run();
}

void WashingMachine::ChangeState(StateName state)
{
    m_prevStateName = m_currentState->WhoAmI();
    m_currentState = m_states[state];
    m_currentState->Reset();
}

IWashingMachineState::State WashingMachine::GetPreviousState() const
{
    return m_prevStateName;
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
