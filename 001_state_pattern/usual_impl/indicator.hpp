#ifndef _INDICATOR_HPP
#define _INDICATOR_HPP

#include "laundry_sensor.hpp"

class Indicator
{
public:
    Indicator() = default;

    enum class WaterLevel
    {
        NONE,
        L1
    };

    void SetLaundryLevel(LaundrySensor::LaundryLevel laundryLevel);
    void SetWaterLevel(WaterLevel laundryLevel);

    bool IsLaundryAvailableIndicatorOn() const;
    LaundrySensor::LaundryLevel GetLaundryWeightLevel() const;
    WaterLevel GetRecommendedWaterLevel() const;

private:
    LaundrySensor::LaundryLevel m_laundryLevel{LaundrySensor::LaundryLevel::NONE};
    WaterLevel m_recommendedWaterLevel{WaterLevel::NONE};
};

#endif  // _INDICATOR_HPP
