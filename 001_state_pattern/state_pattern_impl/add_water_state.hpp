#ifndef _ADD_WATER_STATE_HPP
#define _ADD_WATER_STATE_HPP

#include "Iwashing_machine_state.hpp"

class IWashingCycles;
class IWaterSensor;
class IWashingMachineContext;

class AddWaterState: public IWashingMachineState
{
public:
    AddWaterState(IWashingMachineContext& stateControl, IWaterSensor& laundrySensor,
            IWashingCycles& indicator);

    void Run() override;
    void Reset() override;
    State WhoAmI() { return State::ADD_WATER; }

private:
    bool RecommendedWaterLevelReached();

    IWashingMachineContext& m_context;
    IWaterSensor& m_waterSensor;
    IWashingCycles& m_washCycles;
};

#endif // _ADD_WATER_STATE_HPP
