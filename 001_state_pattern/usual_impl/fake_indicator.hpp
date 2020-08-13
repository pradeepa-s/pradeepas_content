#ifndef _FAKE_INDICATOR_HPP
#define _FAKE_INDICATOR_HPP

#include "Iindicator.hpp"

class FakeIndicator: public IIndicator
{
public:
    FakeIndicator() = default;

    void SetLaundryLevel(LaundryLevel laundryLevel) override;
    void SetWaterLevel(WaterLevel laundryLevel) override;

    bool IsLaundryAvailableIndicatorOn() const;
    LaundryLevel GetLaundryWeightLevel() const;
    WaterLevel GetRecommendedWaterLevel() const;

private:
    LaundryLevel m_laundryLevel{LaundryLevel::NONE};
    WaterLevel m_recommendedWaterLevel{WaterLevel::NONE};
};

#endif  // _FAKE_INDICATOR_HPP
