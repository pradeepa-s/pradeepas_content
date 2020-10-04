#include "standby_state.hpp"
#include "Istate_control.hpp"
#include "Ilaundry_sensor.hpp"
#include "Iindicator.hpp"
#include "Iuser_inputs.hpp"

StandbyState::StandbyState(IWashingMachineContext& stateControl, ILaundrySensor& laundrySensor,
        IIndicator& indicator, IUserInputs& userInputs):
    m_context(stateControl),
    m_laundrySensor(laundrySensor),
    m_indicator(indicator),
    m_userInputs(userInputs)
{}

void StandbyState::Run()
{
    m_indicator.SetLaundryLevel(m_laundrySensor.GetLevel());
    const auto recommendedWaterLevel = m_context.GetRecommendedWaterLevel(m_laundrySensor.GetLevel());
    m_indicator.SetRecommendedWaterLevel(recommendedWaterLevel);

    if (m_userInputs.HasStartButtonPressed())
    {
        m_context.SetWaterLevelTarget(recommendedWaterLevel);
        m_context.ChangeState(IWashingMachineContext::State::ADD_WATER);
    }
}

void StandbyState::Reset()
{
}
