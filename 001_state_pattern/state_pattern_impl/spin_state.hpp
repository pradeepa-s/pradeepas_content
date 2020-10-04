#ifndef _SPIN_STATE_HPP
#define _SPIN_STATE_HPP

#include "Iwashing_machine_state.hpp"

class IWashingCycles;
class IIndicator;
class IWashingMachineContext;

class SpinState: public IWashingMachineState
{
public:
    SpinState(IWashingMachineContext& stateControl, IWashingCycles& washingCycles,
            IIndicator& indicator);

    void Run() override;
    void Reset() override;

private:
    IWashingMachineContext& m_context;
    IWashingCycles& m_washCycles;
    IIndicator& m_indicator;
};

#endif // _SPIN_STATE_HPP
