#include "fake_indicator.hpp"

void FakeIndicator::SetLaundryLevel(LaundryLevel laundryLevel)
{
    m_laundryLevel = laundryLevel;
}

void FakeIndicator::SetRecommendedWaterLevel(WaterLevel waterLevel)
{
    m_recommendedWaterLevel = waterLevel;
}

void FakeIndicator::SetActualWaterLevel(WaterLevel level)
{
    m_actualWaterLevel = level;
}

void FakeIndicator::SetState(MachineState state)
{
    m_washingState = state;
}

IIndicator::MachineState FakeIndicator::GetState() const
{
    return m_washingState;
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

