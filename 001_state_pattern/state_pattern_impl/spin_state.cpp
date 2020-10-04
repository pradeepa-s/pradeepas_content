#include "spin_state.hpp"
#include "Istate_control.hpp"
#include "Iwashing_cycles.hpp"
#include "Iindicator.hpp"

SpinState::SpinState(IWashingMachineContext& stateControl, IWashingCycles& washingCycles,
        IIndicator& indicator):
    m_context(stateControl),
    m_washCycles(washingCycles),
    m_indicator(indicator)
{}

void SpinState::Run()
{
    if (m_washCycles.IsAlgorithmDone())
    {
        m_washCycles.StopSpinAlgorithm();
        m_indicator.SetState(IIndicator::MachineState::DONE);
        m_context.ChangeState(IWashingMachineContext::State::DONE);
    }
}

void SpinState::Reset()
{
    m_washCycles.StartSpinAlgorithm();
    m_indicator.SetState(IIndicator::MachineState::SPIN);
}
