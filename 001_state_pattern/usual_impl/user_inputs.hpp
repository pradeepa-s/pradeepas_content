#ifndef _USER_INPUTS_HPP
#define _USER_INPUTS_HPP

class UserInputs
{
public:
    UserInputs() = default;

    bool HasStartButtonPressed() const;
    
    void PressStart();

private:
    bool m_isStartActive{false};
};

#endif  // _USER_INPUTS_HPP
