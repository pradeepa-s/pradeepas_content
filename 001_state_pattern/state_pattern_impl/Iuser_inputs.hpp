#ifndef _IUSER_INPUTS_HPP
#define _IUSER_INPUTS_HPP

class IUserInputs
{
public:
    virtual bool HasStartButtonPressed() const = 0;
    virtual bool HasStopButtonPressed() const = 0;
};

#endif  // _IUSER_INPUTS_HPP
