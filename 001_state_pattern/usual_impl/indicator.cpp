#include "indicator.hpp"

bool Indicator::IsLaundryAvailableIndicatorOn() const
{
    return m_laundryLevel != LaundrySensor::LaundryLevel::NONE;
}

void Indicator::SetLaundryLevel(LaundrySensor::LaundryLevel laundryLevel)
{
    m_laundryLevel = laundryLevel;
}

void Indicator::SetWaterLevel(WaterLevel waterLevel)
{
    m_recommendedWaterLevel = waterLevel;
}

LaundrySensor::LaundryLevel Indicator::GetLaundryWeightLevel() const
{
    return m_laundryLevel;
}

Indicator::WaterLevel Indicator::GetRecommendedWaterLevel() const
{
    return m_recommendedWaterLevel;
}
