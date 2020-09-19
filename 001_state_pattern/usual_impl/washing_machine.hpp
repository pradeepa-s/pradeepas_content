#ifndef _WASHING_MACHINE_HPP
#define _WASHING_MACHINE_HPP

#include "Iindicator.hpp"
#include "Ilaundry_sensor.hpp"
#include "Iwater_sensor.hpp"

class IUserInputs;
class IWashingCycles;

class WashingMachine
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
        RINSE,
        SPIN,
        DONE,
        ERROR
    };

public:
    WashingMachine(
            ILaundrySensor& laundrySensor, IIndicator& indicator, IUserInputs& userInputs,
            IWashingCycles& washingCycles, IWaterSensor& waterSensor);

    void Run();

private:
    IIndicator::LaundryLevel Convert(ILaundrySensor::LaundryLevel level);
    IIndicator::WaterLevel Convert(IWaterSensor::WaterLevel level);
    IWaterSensor::WaterLevel GetRecommendedWaterLevel(ILaundrySensor::LaundryLevel level);
    WashingMachineState GetPreErrorState(WashingMachineState state);

    WashingMachineState m_state {WashingMachineState::IDLE};
    WashingMachineState m_preErrorState {WashingMachineState::IDLE};
    IWaterSensor::WaterLevel m_recommendedWaterLevel {IWaterSensor::WaterLevel::L2};

    ILaundrySensor& m_laundrySensor;
    IIndicator& m_indicator;
    IUserInputs& m_userInputs;
    IWashingCycles& m_washCycles;
    IWaterSensor& m_waterSensor;

    bool RecommendedWaterLevelReached();
};

#endif  // _WASHING_MACHINE_HPP
