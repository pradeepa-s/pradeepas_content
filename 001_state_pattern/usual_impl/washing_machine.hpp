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
    WashingMachine(
            ILaundrySensor& laundrySensor, IIndicator& indicator, IUserInputs& userInputs,
            IWashingCycles& washingCycles, IWaterSensor& waterSensor);

    void Run();

private:
    IIndicator::LaundryLevel Convert(ILaundrySensor::LaundryLevel level);
    IIndicator::WaterLevel Convert(IWaterSensor::WaterLevel level);
    IWaterSensor::WaterLevel GetRecommendedWaterLevel(ILaundrySensor::LaundryLevel level);

    bool m_started {false};
    bool m_washStarted {false};

    ILaundrySensor& m_laundrySensor;
    IIndicator& m_indicator;
    IUserInputs& m_userInputs;
    IWashingCycles& m_washCycles;
    IWaterSensor& m_waterSensor;
};

#endif  // _WASHING_MACHINE_HPP
