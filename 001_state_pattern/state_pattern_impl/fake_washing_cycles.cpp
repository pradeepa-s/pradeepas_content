#include "fake_washing_cycles.hpp"
#include <iostream>

void FakeWashingCycles::Reset()
{
    m_sequence = "";
    m_washStarted = false;
    m_rinseStarted = false;
    m_spinStarted = false;
    m_error = Error::NONE;
}

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
    m_washStarted = true;
}

void FakeWashingCycles::StartRinseAlgorithm()
{
    m_sequence += "<RinseStarted>";
    m_rinseStarted = true;
}

void FakeWashingCycles::StartSpinAlgorithm()
{
    m_sequence += "<SpinStarted>";
    m_spinStarted = true;
}

void FakeWashingCycles::StopSpinAlgorithm()
{
    m_sequence += "<SpinStopped>";
}

void FakeWashingCycles::ReportError(IWashingCycles::Error error)
{
    m_error = error;
}

void FakeWashingCycles::ClearError()
{
    m_error = IWashingCycles::Error::NONE;
    m_sequence += "<ErrorCleared>";
}

bool FakeWashingCycles::IsInError() const
{
    return m_error != IWashingCycles::Error::NONE;
}

bool FakeWashingCycles::IsAlgorithmDone() const
{
    return !(m_washStarted || m_rinseStarted || m_spinStarted);
}

std::string FakeWashingCycles::GetSequence() const
{
    return m_sequence;
}

void FakeWashingCycles::FinishWash()
{
    m_washStarted = false;
}

void FakeWashingCycles::FinishRinse()
{
    m_rinseStarted = false;
}

void FakeWashingCycles::FinishSpin()
{
    m_spinStarted = false;
}
