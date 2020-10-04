#ifndef _FAKE_INDICATOR_HPP
#define _FAKE_INDICATOR_HPP

#include "Iindicator.hpp"

class FakeIndicator: public IIndicator
{
public:
    FakeIndicator() = default;

    void SetLaundryLevel(LaundryLevel laundryLevel) override;
    void SetLaundryLevel(ILaundrySensor::LaundryLevel laundryLevel) override;
    void SetRecommendedWaterLevel(WaterLevel laundryLevel) override;
    void SetRecommendedWaterLevel(IWaterSensor::WaterLevel laundryLevel) override;
    void SetActualWaterLevel(WaterLevel level) override;
    void SetActualWaterLevel(IWaterSensor::WaterLevel level) override;
    void SetState(MachineState state) override;
    MachineState GetState() const override;

    bool IsLaundryAvailableIndicatorOn() const;
    LaundryLevel GetLaundryWeightLevel() const;
    WaterLevel GetRecommendedWaterLevel() const;
    WaterLevel GetActualWaterLevel() const;

private:
    LaundryLevel m_laundryLevel{LaundryLevel::NONE};
    WaterLevel m_recommendedWaterLevel{WaterLevel::NONE};
    WaterLevel m_actualWaterLevel{WaterLevel::NONE};
    MachineState m_washingState{MachineState::IDLE};
};

#endif  // _FAKE_INDICATOR_HPP
