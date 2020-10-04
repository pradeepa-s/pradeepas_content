#ifndef _IWASHING_MACHINE_STATE_HPP
#define _IWASHING_MACHINE_STATE_HPP

class IWashingMachineState
{
public:
    virtual void Run() = 0;
    virtual void Reset() = 0;

    virtual ~IWashingMachineState() {}
};

#endif //  _IWASHING_MACHINE_STATE_HPP
