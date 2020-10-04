#include "wash_state.hpp"
#include "Istate_control.hpp"
#include "Iindicator.hpp"
#include "Iwashing_cycles.hpp"

WashState::WashState(IWashingMachineContext& stateControl, IIndicator& indicator,
        IWashingCycles& washCycle):
    m_context(stateControl),
    m_indicator(indicator),
    m_washCycles(washCycle)
{}

void WashState::Run()
{
    if (m_washCycles.IsAlgorithmDone())
    {
        m_context.ChangeState(IWashingMachineContext::State::RINSE);
    }
}

void WashState::Reset()
{
    m_washCycles.StartWashAlgorithm();
    m_indicator.SetState(IIndicator::MachineState::WASHING);
}
