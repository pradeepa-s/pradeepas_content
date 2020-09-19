#ifndef _USER_INPUTS_HPP
#define _USER_INPUTS_HPP

#include "Iuser_inputs.hpp"

class FakeUserInputs: public IUserInputs
{
public:
    FakeUserInputs() = default;

    bool HasStartButtonPressed() const override;
    bool HasStopButtonPressed() const override;

    void PressStart();
    void PressStop();
    void Release();

private:
    bool m_isStartActive {false};
    bool m_isStopActive {false};
};

#endif  // _USER_INPUTS_HPP
