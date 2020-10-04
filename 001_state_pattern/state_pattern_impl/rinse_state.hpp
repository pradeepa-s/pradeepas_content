#ifndef _RINSE_STATE_HPP
#define _RINSE_STATE_HPP

#include "Iwashing_machine_state.hpp"

class IWashingCycles;
class IIndicator;
class IWashingMachineContext;

class RinseState: public IWashingMachineState
{
public:
    RinseState(IWashingMachineContext& stateControl, IIndicator& indicator,
            IWashingCycles& washCycle);

    void Run() override;
    void Reset() override;

private:
    IWashingMachineContext& m_context;
    IIndicator& m_indicator;
    IWashingCycles& m_washCycles;
};

#endif // _RINSE_STATE_HPP
