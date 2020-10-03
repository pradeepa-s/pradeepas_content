#include "fake_water_sensor.hpp"

void FakeWaterSensor::SetLevel(const IWaterSensor::WaterLevel level)
{
    m_waterLevel = level;
}

IWaterSensor::WaterLevel FakeWaterSensor::GetLevel() const
{
    return m_waterLevel;
}
