#include "washing_cycles.hpp"

void WashingCycles::StartWater()
{
    m_sequence += "<WaterStarted-SlowSpin>";
}

std::string WashingCycles::GetSequence() const
{
    return m_sequence;
}
