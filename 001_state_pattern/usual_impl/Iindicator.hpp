#ifndef _IINDICATOR_HPP
#define _IINDICATOR_HPP

#include "Ilaundry_sensor.hpp"

class IIndicator
{
public:
    enum class WaterLevel
    {
        NONE,
        L1,
        L2
    };

    enum class LaundryLevel
    {
        NONE,
        L1,
        L2
    };

    enum class MachineState
    {
        WASHING,
        RINSE,
        SPIN,
        DONE,
        ERROR
    };

    virtual void SetLaundryLevel(LaundryLevel laundryLevel) = 0;
    virtual void SetRecommendedWaterLevel(WaterLevel laundryLevel) = 0;
    virtual void SetActualWaterLevel(WaterLevel level) = 0;
    virtual void SetState(MachineState state) = 0;
    virtual MachineState GetState() const = 0;
};

#endif  // _IINDICATOR_HPP
