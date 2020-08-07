#ifndef _LAUNDRY_SENSOR_HPP
#define _LAUNDRY_SENSOR_HPP

class LaundrySensor
{
public:
    LaundrySensor() = default;

    bool IsAvailable() const;

    void AddLaundry();

private:
    bool m_isLaundyAvailable{false};
};

#endif  // _LAUNDRY_SENSOR_HPP
