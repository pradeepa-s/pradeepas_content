#include "fake_user_inputs.hpp"

bool FakeUserInputs::HasStartButtonPressed() const
{
    return m_isStartActive;
}

void FakeUserInputs::PressStart()
{
    m_isStartActive = true;
}

void FakeUserInputs::Release()
{
    m_isStartActive = false;
}
