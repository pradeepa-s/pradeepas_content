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
    void StartRinseAlgorithm() override;
    void StartSpinAlgorithm() override;
    void StopSpinAlgorithm() override;
    bool IsAlgorithmDone() const override;

    std::string GetSequence() const;
    void FinishWash();
    void FinishRinse();
    void FinishSpin();

private:
    std::string m_sequence{""};
    bool m_washStarted {false};
    bool m_rinseStarted {false};
    bool m_spinStarted {false};
};

#endif  // _FAKE_WASHING_CYCLES_HPP
