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

void FakeWashingCycles::StartRinseAlgorithm()
{
    m_sequence += "<RinseStarted>";
}

bool FakeWashingCycles::IsAlgorithmDone() const
{
    return m_washFinished;
}

std::string FakeWashingCycles::GetSequence() const
{
    return m_sequence;
}

void FakeWashingCycles::FinishWash()
{
    m_washFinished = true;
}
