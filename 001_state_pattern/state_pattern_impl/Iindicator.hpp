#ifndef _IINDICATOR_HPP
#define _IINDICATOR_HPP

#include "Ilaundry_sensor.hpp"
#include "Iwater_sensor.hpp"

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
        IDLE,
        WASHING,
        RINSE,
        SPIN,
        DONE,
        ERROR
    };

    virtual void SetLaundryLevel(LaundryLevel laundryLevel) = 0;
    virtual void SetLaundryLevel(ILaundrySensor::LaundryLevel laundryLevel) = 0;
    virtual void SetRecommendedWaterLevel(WaterLevel waterLevel) = 0;
    virtual void SetRecommendedWaterLevel(IWaterSensor::WaterLevel waterLevel) = 0;
    virtual void SetActualWaterLevel(WaterLevel level) = 0;
    virtual void SetActualWaterLevel(IWaterSensor::WaterLevel level) = 0;
    virtual void SetState(MachineState state) = 0;
    virtual MachineState GetState() const = 0;

    virtual ~IIndicator() {}
};

#endif  // _IINDICATOR_HPP
