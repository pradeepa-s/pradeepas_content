#ifndef _LAUNDRY_SENSOR_HPP
#define _LAUNDRY_SENSOR_HPP

class LaundrySensor
{
public:
    LaundrySensor() = default;

    enum class LaundryLevel
    {
        NONE,
        L1,
        L2
    };

    bool IsEmpty() const;
    LaundryLevel GetLevel() const;

    void AddLaundry(LaundryLevel laundryLevel);

private:
    LaundryLevel m_laundryLevel{LaundryLevel::NONE};
};

#endif  // _LAUNDRY_SENSOR_HPP
