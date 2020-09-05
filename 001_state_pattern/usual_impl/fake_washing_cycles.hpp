#ifndef _FAKE_WASHING_CYCLES_HPP
#define _FAKE_WASHING_CYCLES_HPP

#include "Iwashing_cycles.hpp"
#include <string>

class FakeWashingCycles: public IWashingCycles
{
public:
    FakeWashingCycles() = default;

    void StartWater() override;
    void StopWater() override;
    void StartWashAlgorithm() override;

    std::string GetSequence() const;

private:
    std::string m_sequence{""};
};

#endif  // _FAKE_WASHING_CYCLES_HPP
