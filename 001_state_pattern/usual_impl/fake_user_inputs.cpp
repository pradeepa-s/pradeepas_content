#include "fake_user_inputs.hpp"

bool FakeUserInputs::HasStartButtonPressed() const
{
    return m_isStartActive;
}

bool FakeUserInputs::HasStopButtonPressed() const
{
    return m_isStopActive;
}

void FakeUserInputs::PressStart()
{
    m_isStartActive = true;
}

void FakeUserInputs::PressStop()
{
    m_isStopActive = true;
}

void FakeUserInputs::Release()
{
    m_isStartActive = false;
    m_isStopActive = false;
}
