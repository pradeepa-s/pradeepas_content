#ifndef _WASH_STATE_HPP
#define _WASH_STATE_HPP

#include "Iwashing_machine_state.hpp"

class IWashingCycles;
class IIndicator;
class IWashingMachineContext;

class WashState: public IWashingMachineState
{
public:
    WashState(IWashingMachineContext& stateControl, IIndicator& indicator,
            IWashingCycles& washCycle);

    void Run() override;
    void Reset() override;

private:
    IWashingMachineContext& m_context;
    IIndicator& m_indicator;
    IWashingCycles& m_washCycles;
};

#endif // _WASH_STATE_HPP
