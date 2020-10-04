#ifndef _ISTATE_CONTROL
#define _ISTATE_CONTROL

#include "Iindicator.hpp"
#include "Iwater_sensor.hpp"

class IWashingMachineContext
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

    virtual void ChangeState(State state) = 0;

    virtual IIndicator::LaundryLevel Convert(ILaundrySensor::LaundryLevel level) = 0;
    virtual IIndicator::WaterLevel Convert(IWaterSensor::WaterLevel level) = 0;
    virtual IWaterSensor::WaterLevel GetRecommendedWaterLevel(ILaundrySensor::LaundryLevel level) = 0;
    virtual void SetWaterLevelTarget(IWaterSensor::WaterLevel level) = 0;
    virtual IWaterSensor::WaterLevel GetWaterLevelTarget() const = 0;

    virtual ~IWashingMachineContext() {};
};

#endif  //  _ISTATE_CONTROL
