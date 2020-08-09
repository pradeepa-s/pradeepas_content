#ifndef _WASHING_CYCLES_HPP
#define _WASHING_CYCLES_HPP

#include <string>

class WashingCycles
{
public:
    WashingCycles() = default;

    void StartWater();
    
    std::string GetSequence() const;

private:
    std::string m_sequence{""};
};

#endif  // _WASHING_CYCLES_HPP
