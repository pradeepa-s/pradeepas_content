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

    virtual void SetLaundryLevel(LaundryLevel laundryLevel) = 0;
    virtual void SetWaterLevel(WaterLevel laundryLevel) = 0;
};

#endif  // _IINDICATOR_HPP