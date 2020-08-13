#ifndef _LAUNDRY_SENSOR_HPP
#define _LAUNDRY_SENSOR_HPP

#include "Ilaundry_sensor.hpp"

class FakeLaundrySensor: public ILaundrySensor
{
public:
    FakeLaundrySensor() = default;

    bool IsEmpty() const;
    LaundryLevel GetLevel() const;

    void AddLaundry(LaundryLevel laundryLevel);

private:
    LaundryLevel m_laundryLevel{LaundryLevel::NONE};
};

#endif  // _LAUNDRY_SENSOR_HPP
