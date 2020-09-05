#include "fake_indicator.hpp"

void FakeIndicator::SetLaundryLevel(LaundryLevel laundryLevel)
{
    m_laundryLevel = laundryLevel;
}

void FakeIndicator::SetWaterLevel(WaterLevel waterLevel)
{
    m_recommendedWaterLevel = waterLevel;
}

void FakeIndicator::SetActualWaterLevel(WaterLevel level)
{
    m_actualWaterLevel = level;
}

IIndicator::LaundryLevel FakeIndicator::GetLaundryWeightLevel() const
{
    return m_laundryLevel;
}

bool FakeIndicator::IsLaundryAvailableIndicatorOn() const
{
    return m_laundryLevel != LaundryLevel::NONE;
}

IIndicator::WaterLevel FakeIndicator::GetActualWaterLevel() const
{
    return m_actualWaterLevel;
}

IIndicator::WaterLevel FakeIndicator::GetRecommendedWaterLevel() const
{
    return m_recommendedWaterLevel;
}

