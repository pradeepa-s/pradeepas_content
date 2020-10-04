#ifndef _DONE_STATE_HPP
#define _DONE_STATE_HPP

#include "Iwashing_machine_state.hpp"

class ILaundrySensor;
class IIndicator;
class IWashingMachineContext;

class DoneState: public IWashingMachineState
{
public:
    DoneState(IWashingMachineContext& stateControl, ILaundrySensor& laundrySensor,
            IIndicator& indicator);

    void Run() override;
    void Reset() override;

private:
    IWashingMachineContext& m_context;
    ILaundrySensor& m_laundrySensor;
    IIndicator& m_indicator;
};

#endif // _DONE_STATE_HPP
