#include "laundry_sensor.hpp"

void LaundrySensor::AddLaundry()
{
    m_isLaundyAvailable = true;
}

bool LaundrySensor::IsAvailable() const
{
    return m_isLaundyAvailable;
}
