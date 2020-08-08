#include "laundry_sensor.hpp"

void LaundrySensor::AddLaundry(LaundrySensor::LaundryLevel laundryLevel)
{
    m_laundryLevel = laundryLevel;
}

bool LaundrySensor::IsEmpty() const
{
    return m_laundryLevel != LaundrySensor::LaundryLevel::NONE;
}

LaundrySensor::LaundryLevel LaundrySensor::GetLevel() const
{
    return m_laundryLevel;
}
