#include "done_state.hpp"
#include "Istate_control.hpp"
#include "Ilaundry_sensor.hpp"
#include "Iindicator.hpp"

DoneState::DoneState(IWashingMachineContext& stateControl, ILaundrySensor& laundrySensor,
        IIndicator& indicator):
    m_context(stateControl),
    m_laundrySensor(laundrySensor),
    m_indicator(indicator)
{}

void DoneState::Run()
{
    if (m_laundrySensor.GetLevel() == ILaundrySensor::LaundryLevel::NONE)
    {
        m_indicator.SetLaundryLevel(m_laundrySensor.GetLevel());
        m_indicator.SetRecommendedWaterLevel(IIndicator::WaterLevel::NONE);
        m_context.ChangeState(IWashingMachineContext::State::IDLE);
    }
}

void DoneState::Reset()
{
}
