#ifndef _FAKE_WATER_SENSOR_HPP
#define _FAKE_WATER_SENSOR_HPP

#include "Iwater_sensor.hpp"

class FakeWaterSensor: public IWaterSensor
{
public:
    FakeWaterSensor() = default;

    void SetLevel(const WaterLevel level) override;
    WaterLevel GetLevel() const override;

private:
    WaterLevel m_waterLevel{WaterLevel::NONE};
};

#endif  // _FAKE_WATER_SENSOR_HPP
