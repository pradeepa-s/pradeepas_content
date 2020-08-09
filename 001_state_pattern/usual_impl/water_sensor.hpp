#ifndef _WATER_SENSOR_HPP
#define _WATER_SENSOR_HPP

class WaterSensor
{
public:
    WaterSensor() = default;

    enum class WaterLevel
    {
        NONE,
        L1
    };

    void SetLevel();



#endif  // _WATER_SENSOR_HPP
