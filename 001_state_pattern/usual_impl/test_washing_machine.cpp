#include "gtest/gtest.h"
#include "washing_machine.hpp"
#include "fake_indicator.hpp"
#include "fake_laundry_sensor.hpp"
#include "fake_user_inputs.hpp"
#include "fake_washing_cycles.hpp"
#include "fake_water_sensor.hpp"

class TestWashingMachineStates: public ::testing::Test
{
protected:
    TestWashingMachineStates():
        m_laundrySensor(), m_indicator(), m_userInputs(), m_washCycle(), m_waterSensor(),
        m_iut(m_laundrySensor, m_indicator, m_userInputs, m_washCycle, m_waterSensor)
    {
    }

protected:
    void RunEnough()
    {
        const int ENOUGH_REPS = 10;
        for (int i = 0; i < ENOUGH_REPS; i++)
        {
            m_iut.Run();
        }
    }

    FakeLaundrySensor m_laundrySensor;
    FakeIndicator m_indicator;
    FakeUserInputs m_userInputs;
    FakeWashingCycles m_washCycle;
    FakeWaterSensor m_waterSensor;
    WashingMachine m_iut;
};

TEST_F(TestWashingMachineStates, ShallIdentifyNoCloths)
{
    RunEnough();
    EXPECT_FALSE(m_indicator.IsLaundryAvailableIndicatorOn());
}

TEST_F(TestWashingMachineStates, ShallIdentifyCloths)
{
    m_laundrySensor.AddLaundry(ILaundrySensor::LaundryLevel::L1);
    RunEnough();
    EXPECT_TRUE(m_indicator.IsLaundryAvailableIndicatorOn());
}

TEST_F(TestWashingMachineStates, ShallIndicateLaundryWeight)
{
    m_laundrySensor.AddLaundry(ILaundrySensor::LaundryLevel::L1);
    RunEnough();
    EXPECT_EQ(IIndicator::LaundryLevel::L1, m_indicator.GetLaundryWeightLevel());

    m_laundrySensor.AddLaundry(ILaundrySensor::LaundryLevel::L2);
    RunEnough();
    EXPECT_EQ(IIndicator::LaundryLevel::L2, m_indicator.GetLaundryWeightLevel());
}

TEST_F(TestWashingMachineStates, ShallIndicateRecommendedWaterNone)
{
    RunEnough();
    EXPECT_EQ(IIndicator::WaterLevel::NONE, m_indicator.GetRecommendedWaterLevel());
}

TEST_F(TestWashingMachineStates, ShallIndicateRecommendedWaterLevel)
{
    m_laundrySensor.AddLaundry(ILaundrySensor::LaundryLevel::L1);
    RunEnough();
    EXPECT_EQ(IIndicator::WaterLevel::L1, m_indicator.GetRecommendedWaterLevel());

    m_laundrySensor.AddLaundry(ILaundrySensor::LaundryLevel::L2);
    RunEnough();
    EXPECT_EQ(IIndicator::WaterLevel::L2, m_indicator.GetRecommendedWaterLevel());
}

TEST_F(TestWashingMachineStates, ShallStartWaterAfterStartIsPressed)
{
    m_laundrySensor.AddLaundry(ILaundrySensor::LaundryLevel::L1);
    RunEnough();

    m_userInputs.PressStart();
    RunEnough();
    EXPECT_STREQ("<WaterStarted-SlowSpin>", m_washCycle.GetSequence().c_str());
}

TEST_F(TestWashingMachineStates, ShallIndicateCurrentWaterLevelAfterStartIsPressed)
{
    m_laundrySensor.AddLaundry(ILaundrySensor::LaundryLevel::L1);
    RunEnough();

    m_userInputs.PressStart();
    RunEnough();
    EXPECT_EQ(IIndicator::WaterLevel::NONE, m_indicator.GetActualWaterLevel());

    m_waterSensor.SetLevel(IWaterSensor::WaterLevel::L1);
    RunEnough();
    EXPECT_EQ(IIndicator::WaterLevel::L1, m_indicator.GetActualWaterLevel());

    m_waterSensor.SetLevel(IWaterSensor::WaterLevel::L2);
    RunEnough();
    EXPECT_EQ(IIndicator::WaterLevel::L2, m_indicator.GetActualWaterLevel());
}


TEST_F(TestWashingMachineStates, ShallStartWashingCycleOnceTheWaterLevelReachedTheRecommendedLevel)
{
    m_laundrySensor.AddLaundry(ILaundrySensor::LaundryLevel::L2);
    RunEnough();

    m_userInputs.PressStart();
    RunEnough();

    m_waterSensor.SetLevel(IWaterSensor::WaterLevel::L2);
    RunEnough();

    EXPECT_STREQ("<WaterStarted-SlowSpin><WaterStopped><WashAlgoStarted>",
            m_washCycle.GetSequence().c_str());
}
