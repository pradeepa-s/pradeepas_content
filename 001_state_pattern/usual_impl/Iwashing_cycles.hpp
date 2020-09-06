#ifndef _IWASHING_CYCLES_HPP
#define _IWASHING_CYCLES_HPP


class IWashingCycles
{
public:
    virtual void StartWater() = 0;
    virtual void StopWater() = 0;
    virtual void StartWashAlgorithm() = 0;
    virtual void StartRinseAlgorithm() = 0;
    virtual void StartSpinAlgorithm() = 0;
    virtual void StopSpinAlgorithm() = 0;
    virtual bool IsAlgorithmDone() const = 0;
};

#endif  // _IWASHING_CYCLES_HPP
