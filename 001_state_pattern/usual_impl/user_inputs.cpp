#include "user_inputs.hpp"

bool UserInputs::HasStartButtonPressed() const
{
    return m_isStartActive;
}

void UserInputs::PressStart()
{
    m_isStartActive = true;
}
