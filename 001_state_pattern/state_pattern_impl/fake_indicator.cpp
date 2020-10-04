#include "fake_indicator.hpp"

void FakeIndicator::SetLaundryLevel(LaundryLevel laundryLevel)
{
    m_laundryLevel = laundryLevel;
}

void FakeIndicator::SetLaundryLevel(ILaundrySensor::LaundryLevel laundryLevel)
{
    LaundryLevel indicatorLevel {};
    switch (laundryLevel)
    {
        case ILaundrySensor::LaundryLevel::NONE:
            indicatorLevel = IIndicator::LaundryLevel::NONE;
            break;
        case ILaundrySensor::LaundryLevel::L1:
            indicatorLevel = IIndicator::LaundryLevel::L1;
            break;
        case ILaundrySensor::LaundryLevel::L2:
            indicatorLevel = IIndicator::LaundryLevel::L2;
            break;
    }

    SetLaundryLevel(indicatorLevel);
}

void FakeIndicator::SetRecommendedWaterLevel(WaterLevel waterLevel)
{
    m_recommendedWaterLevel = waterLevel;
}

void FakeIndicator::SetRecommendedWaterLevel(IWaterSensor::WaterLevel level)
{
    WaterLevel indicatorLevel = WaterLevel::NONE;
    switch (level)
    {
        case IWaterSensor::WaterLevel::NONE:
            indicatorLevel = WaterLevel::NONE;
            break;
        case IWaterSensor::WaterLevel::L1:
            indicatorLevel = WaterLevel::L1;
            break;
        case IWaterSensor::WaterLevel::L2:
            indicatorLevel = WaterLevel::L2;
            break;
    }

    SetRecommendedWaterLevel(indicatorLevel);
}

void FakeIndicator::SetActualWaterLevel(WaterLevel level)
{
    m_actualWaterLevel = level;
}

void FakeIndicator::SetActualWaterLevel(IWaterSensor::WaterLevel level)
{
    WaterLevel indicatorLevel = WaterLevel::NONE;
    switch (level)
    {
        case IWaterSensor::WaterLevel::NONE:
            indicatorLevel = WaterLevel::NONE;
            break;
        case IWaterSensor::WaterLevel::L1:
            indicatorLevel = WaterLevel::L1;
            break;
        case IWaterSensor::WaterLevel::L2:
            indicatorLevel = WaterLevel::L2;
            break;
    }
    m_actualWaterLevel = indicatorLevel;
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

