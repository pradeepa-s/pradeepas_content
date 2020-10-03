#ifndef _ILAUNDRY_SENSOR_HPP
#define _ILAUNDRY_SENSOR_HPP

class ILaundrySensor
{
public:
    enum class LaundryLevel
    {
        NONE,
        L1,
        L2
    };

    virtual bool IsEmpty() const = 0;
    virtual LaundryLevel GetLevel() const = 0;

    virtual ~ILaundrySensor() {}
};

#endif  // _ILAUNDRY_SENSOR_HPP
