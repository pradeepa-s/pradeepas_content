#include "fake_washing_cycles.hpp"

void FakeWashingCycles::StartWater()
{
    m_sequence += "<WaterStarted-SlowSpin>";
}

void FakeWashingCycles::StopWater()
{
    m_sequence += "<WaterStopped>";
}

void FakeWashingCycles::StartWashAlgorithm()
{
    m_sequence += "<WashAlgoStarted>";
}

std::string FakeWashingCycles::GetSequence() const
{
    return m_sequence;
}
