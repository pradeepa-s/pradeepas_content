#include "indicator.hpp"

bool Indicator::GetClothIndicator() const
{
    return m_laundryState;
}

void Indicator::Set(bool state)
{
    m_laundryState = state;
}
