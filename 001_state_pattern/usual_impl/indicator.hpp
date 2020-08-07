#ifndef _INDICATOR_HPP
#define _INDICATOR_HPP

class Indicator
{
public:
    Indicator() = default;

    void Set(bool state);

    bool GetClothIndicator() const;

private:
    bool m_laundryState{false};
};

#endif  // _INDICATOR_HPP
