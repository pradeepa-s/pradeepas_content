#ifndef _WASHING_MACHINE_HPP
#define _WASHING_MACHINE_HPP

#include <map>
#include <memory>
#include "Iindicator.hpp"
#include "Ilaundry_sensor.hpp"
#include "Iwater_sensor.hpp"
#include "Istate_control.hpp"

class IUserInputs;
class IWashingCycles;
class IWashingMachineState;

class WashingMachine: public IWashingMachineContext
{
private:
    using State = std::shared_ptr<IWashingMachineState>;
    using StateName = IWashingMachineState::State;
    using StateMap = std::map<StateName, State>;

public:
    WashingMachine(
            ILaundrySensor& laundrySensor, IIndicator& indicator, IUserInputs& userInputs,
            IWashingCycles& washingCycles, IWaterSensor& waterSensor);

    void Run();

    // IWashingMachineContext interface
    void ChangeState(StateName state) override;
    IWaterSensor::WaterLevel GetRecommendedWaterLevel(ILaundrySensor::LaundryLevel level) override;
    void SetWaterLevelTarget(IWaterSensor::WaterLevel level) override;
    IWaterSensor::WaterLevel GetWaterLevelTarget() const override;
    StateName GetPreviousState() const override;

private:
    ILaundrySensor& m_laundrySensor;
    IIndicator& m_indicator;
    IUserInputs& m_userInputs;
    IWashingCycles& m_washCycles;
    IWaterSensor& m_waterSensor;
    State m_currentState;
    StateName m_prevStateName;
    IWaterSensor::WaterLevel m_waterLevelTarget;
    StateMap m_states;
};

#endif  // _WASHING_MACHINE_HPP
