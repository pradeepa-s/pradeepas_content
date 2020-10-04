#ifndef _STANDBY_STATE_HPP
#define _STANDBY_STATE_HPP

#include "Iwashing_machine_state.hpp"

class IIndicator;
class IUserInputs;
class ILaundrySensor;
class IWashingMachineContext;

class StandbyState: public IWashingMachineState
{
public:
    StandbyState(IWashingMachineContext& stateControl, ILaundrySensor& laundrySensor,
            IIndicator& indicator, IUserInputs& userInputs);

    void Run() override;
    void Reset() override;

private:
    IWashingMachineContext& m_context;
    ILaundrySensor& m_laundrySensor;
    IIndicator& m_indicator;
    IUserInputs& m_userInputs;
};

#endif // _STANDBY_STATE_HPP
