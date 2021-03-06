#ifndef _IWATER_SENSOR_HPP
#define _IWATER_SENSOR_HPP

class IWaterSensor
{
public:
    enum class WaterLevel
    {
        NONE,
        L1,
        L2
    };

    virtual void SetLevel(const WaterLevel level) = 0;
    virtual WaterLevel GetLevel() const = 0;

    virtual ~IWaterSensor() {}
};

#endif  // _IWATER_SENSOR_HPP
