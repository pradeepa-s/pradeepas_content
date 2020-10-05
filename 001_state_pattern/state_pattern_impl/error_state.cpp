#include "error_state.hpp"
#include "Istate_control.hpp"
#include "Iwashing_cycles.hpp"
#include "Iindicator.hpp"
#include "Iuser_inputs.hpp"

ErrorState::ErrorState(IWashingMachineContext& stateControl, IWashingCycles& washingCycles,
        IIndicator& indicator, IUserInputs& userInputs):
    m_context(stateControl),
    m_washCycles(washingCycles),
    m_indicator(indicator),
    m_userInputs(userInputs)
{}

void ErrorState::Run()
{
    if (m_userInputs.HasStartButtonPressed())
    {
        m_washCycles.ClearError();
        m_context.ChangeState(m_preErrorState);
    }
    else if (m_userInputs.HasStopButtonPressed())
    {
        m_washCycles.Reset();
        m_indicator.SetState(IIndicator::MachineState::IDLE);
        m_context.ChangeState(IWashingMachineState::State::IDLE);
    }
}

void ErrorState::Reset()
{
    m_indicator.SetState(IIndicator::MachineState::ERROR);
    m_preErrorState = m_context.GetPreviousState();
}

