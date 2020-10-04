#include "rinse_state.hpp"
#include "Istate_control.hpp"
#include "Iindicator.hpp"
#include "Iwashing_cycles.hpp"

RinseState::RinseState(IWashingMachineContext& stateControl, IIndicator& indicator,
        IWashingCycles& washCycle):
    m_context(stateControl),
    m_indicator(indicator),
    m_washCycles(washCycle)
{}

void RinseState::Run()
{
    if (m_washCycles.IsAlgorithmDone())
    {
        m_context.ChangeState(IWashingMachineState::State::SPIN);
    }
}

void RinseState::Reset()
{
    m_washCycles.StartRinseAlgorithm();
    m_indicator.SetState(IIndicator::MachineState::RINSE);
}
