#ifndef _WASHING_MACHINE_HPP
#define _WASHING_MACHINE_HPP

class LaundrySensor;
class Indicator;

class WashingMachine
{
public:
    WashingMachine(LaundrySensor& laundrySensor, Indicator& indicator);

    void Run();

private:
    LaundrySensor& m_laundrySensor;
    Indicator& m_indicator;
};

#endif  // _WASHING_MACHINE_HPP
