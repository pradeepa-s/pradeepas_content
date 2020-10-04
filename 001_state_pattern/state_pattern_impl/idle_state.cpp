#include "idle_state.hpp"
#include "Istate_control.hpp"
#include "Ilaundry_sensor.hpp"

IdleState::IdleState(IWashingMachineContext& stateControl, ILaundrySensor& laundrySensor):
    m_context(stateControl),
    m_laundrySensor(laundrySensor)
{}

void IdleState::Run()
{
    if (m_laundrySensor.GetLevel() != ILaundrySensor::LaundryLevel::NONE)
    {
        m_context.ChangeState(IWashingMachineState::State::STANDBY);
    }
}

void IdleState::Reset()
{
}
