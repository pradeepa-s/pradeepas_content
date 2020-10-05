#ifndef _ERROR_STATE_HPP
#define _ERROR_STATE_HPP

#include "Iwashing_machine_state.hpp"

class IWashingCycles;
class IIndicator;
class IWashingMachineContext;
class IUserInputs;

class ErrorState: public IWashingMachineState
{
public:
    ErrorState(IWashingMachineContext& stateControl, IWashingCycles& washingCycles,
            IIndicator& indicator, IUserInputs& userInputs);

    void Run() override;
    void Reset() override;
    State WhoAmI() { return State::ERROR; }

private:
    IWashingMachineContext& m_context;
    IWashingCycles& m_washCycles;
    IIndicator& m_indicator;
    IUserInputs& m_userInputs;
    IWashingMachineState::State m_preErrorState;
};

#endif // _ERROR_STATE_HPP
