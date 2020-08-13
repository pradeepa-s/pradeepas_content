#include "fake_laundry_sensor.hpp"

void FakeLaundrySensor::AddLaundry(ILaundrySensor::LaundryLevel laundryLevel)
{
    m_laundryLevel = laundryLevel;
}

bool FakeLaundrySensor::IsEmpty() const
{
    return m_laundryLevel != ILaundrySensor::LaundryLevel::NONE;
}

ILaundrySensor::LaundryLevel FakeLaundrySensor::GetLevel() const
{
    return m_laundryLevel;
}
