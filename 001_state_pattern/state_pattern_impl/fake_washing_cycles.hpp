#ifndef _FAKE_WASHING_CYCLES_HPP
#define _FAKE_WASHING_CYCLES_HPP

#include "Iwashing_cycles.hpp"
#include <string>

class FakeWashingCycles: public IWashingCycles
{
public:
    FakeWashingCycles() = default;

    void Reset() override;
    void StartWater() override;
    void StopWater() override;
    void StartWashAlgorithm() override;
    void StartRinseAlgorithm() override;
    void StartSpinAlgorithm() override;
    void StopSpinAlgorithm() override;
    bool IsAlgorithmDone() const override;
    bool IsInError() const override;
    void ClearError() override;

    std::string GetSequence() const;
    void FinishWash();
    void FinishRinse();
    void FinishSpin();
    void ReportError(Error error);

private:
    std::string m_sequence{""};
    bool m_washStarted {false};
    bool m_rinseStarted {false};
    bool m_spinStarted {false};
    Error m_error {Error::NONE};
};

#endif  // _FAKE_WASHING_CYCLES_HPP
