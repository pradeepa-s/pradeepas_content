#include "fake_washing_cycles.hpp"

void FakeWashingCycles::StartWater()
{
    m_sequence += "<WaterStarted-SlowSpin>";
}

std::string FakeWashingCycles::GetSequence() const
{
    return m_sequence;
}
