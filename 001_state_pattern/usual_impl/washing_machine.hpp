#ifndef _WASHING_MACHINE_HPP
#define _WASHING_MACHINE_HPP

#include "Iindicator.hpp"
#include "Ilaundry_sensor.hpp"

class IUserInputs;
class IWashingCycles;

class WashingMachine
{
public:
    WashingMachine(
            ILaundrySensor& laundrySensor, IIndicator& indicator, IUserInputs& userInputs,
            IWashingCycles& washingCycles);

    void Run();

private:
    IIndicator::LaundryLevel Convert(ILaundrySensor::LaundryLevel level);
    ILaundrySensor& m_laundrySensor;
    IIndicator& m_indicator;
    IUserInputs& m_userInputs;
    IWashingCycles& m_washCycles;
};

#endif  // _WASHING_MACHINE_HPP
