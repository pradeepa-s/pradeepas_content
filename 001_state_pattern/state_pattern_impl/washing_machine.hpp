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
public:
    enum class WashingMachineState
    {
        IDLE,
        STANDBY,
        STARTING_WATER,
        ADD_WATER,
        STARTING_WASH,
        WASH,
        STARTING_RINSE,
        RINSE,
        STARTING_SPIN,
        SPIN,
        DONE,
        ERROR
    };

public:
    WashingMachine(
            ILaundrySensor& laundrySensor, IIndicator& indicator, IUserInputs& userInputs,
            IWashingCycles& washingCycles, IWaterSensor& waterSensor);

    void Run();
    void Run2();
    void ChangeState(IWashingMachineState::State state) override;
    IWaterSensor::WaterLevel GetRecommendedWaterLevel(ILaundrySensor::LaundryLevel level) override;
    void SetWaterLevelTarget(IWaterSensor::WaterLevel level) override;
    IWaterSensor::WaterLevel GetWaterLevelTarget() const override;
    IWashingMachineState::State GetPreviousState() const override;

private:
    using State = std::shared_ptr<IWashingMachineState>;

    IIndicator::LaundryLevel Convert(ILaundrySensor::LaundryLevel level);
    IIndicator::WaterLevel Convert(IWaterSensor::WaterLevel level);
    WashingMachineState GetPreErrorState(WashingMachineState state);

    WashingMachineState m_state {WashingMachineState::IDLE};
    WashingMachineState m_preErrorState {WashingMachineState::IDLE};
    IWashingMachineState::State m_prevStateName {};
    IWaterSensor::WaterLevel m_recommendedWaterLevel {IWaterSensor::WaterLevel::L2};
    IWaterSensor::WaterLevel m_waterLevelTarget {IWaterSensor::WaterLevel::L2};

    ILaundrySensor& m_laundrySensor;
    IIndicator& m_indicator;
    IUserInputs& m_userInputs;
    IWashingCycles& m_washCycles;
    IWaterSensor& m_waterSensor;

    State m_currentState {nullptr};

    bool RecommendedWaterLevelReached();
    std::map<IWashingMachineState::State, State> m_states;
};

#endif  // _WASHING_MACHINE_HPP
