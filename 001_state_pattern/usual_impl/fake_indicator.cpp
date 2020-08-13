#include "fake_indicator.hpp"

bool FakeIndicator::IsLaundryAvailableIndicatorOn() const
{
    return m_laundryLevel != LaundryLevel::NONE;
}

void FakeIndicator::SetLaundryLevel(LaundryLevel laundryLevel)
{
    m_laundryLevel = laundryLevel;
}

void FakeIndicator::SetWaterLevel(WaterLevel waterLevel)
{
    m_recommendedWaterLevel = waterLevel;
}

IIndicator::LaundryLevel FakeIndicator::GetLaundryWeightLevel() const
{
    return m_laundryLevel;
}

IIndicator::WaterLevel FakeIndicator::GetRecommendedWaterLevel() const
{
    return m_recommendedWaterLevel;
}
