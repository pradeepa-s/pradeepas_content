#ifndef _WASHING_MACHINE_HPP
#define _WASHING_MACHINE_HPP

class LaundrySensor;
class Indicator;
class UserInputs;
class WashingCycles;

class WashingMachine
{
public:
    WashingMachine(
            LaundrySensor& laundrySensor, Indicator& indicator, UserInputs& userInputs,
            WashingCycles& washingCycles);

    void Run();

private:
    LaundrySensor& m_laundrySensor;
    Indicator& m_indicator;
    UserInputs& m_userInputs;
    WashingCycles& m_washCycles;
};

#endif  // _WASHING_MACHINE_HPP
