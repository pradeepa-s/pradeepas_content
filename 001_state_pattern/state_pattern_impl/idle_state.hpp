#ifndef _IDLE_STATE_HPP
#define _IDLE_STATE_HPP

#include "Iwashing_machine_state.hpp"

class ILaundrySensor;
class IWashingMachineContext;

class IdleState: public IWashingMachineState
{
public:
    IdleState(IWashingMachineContext& stateControl, ILaundrySensor& laundrySensor);

    void Run() override;
    void Reset() override;

private:
    IWashingMachineContext& m_context;
    ILaundrySensor& m_laundrySensor;
};

#endif // _IDLE_STATE_HPP
