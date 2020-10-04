#ifndef _IWASHING_MACHINE_STATE_HPP
#define _IWASHING_MACHINE_STATE_HPP

class IWashingMachineState
{
public:
    enum class State
    {
        IDLE,
        STANDBY,
        ADD_WATER,
        WASH,
        RINSE,
        SPIN,
        DONE,
        ERROR
    };

    virtual void Run() = 0;
    virtual void Reset() = 0;
    virtual State WhoAmI() = 0;

    virtual ~IWashingMachineState() {}
};

#endif //  _IWASHING_MACHINE_STATE_HPP
