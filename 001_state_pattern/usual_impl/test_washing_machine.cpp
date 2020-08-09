#include "gtest/gtest.h"
#include "washing_machine.hpp"
#include "indicator.hpp"
#include "laundry_sensor.hpp"
#include "user_inputs.hpp"
#include "washing_cycles.hpp"
#include "water_sensor.hpp"

class TestWashingMachineStates: public ::testing::Test
{
protected:
    TestWashingMachineStates():
        m_laundrySensor(), m_indicator(), m_userInputs(), m_washCycle(), m_waterSensor(),
        m_iut(m_laundrySensor, m_indicator, m_userInputs, m_washCycle)
    {
    }

protected:
    LaundrySensor m_laundrySensor;
    Indicator m_indicator;
    UserInputs m_userInputs;
    WashingCycles m_washCycle;
    WaterSensor m_waterSensor;
    WashingMachine m_iut;
};

TEST_F(TestWashingMachineStates, ShallIdentifyNoCloths)
{
    m_iut.Run();
    EXPECT_FALSE(m_indicator.IsLaundryAvailableIndicatorOn());
}

TEST_F(TestWashingMachineStates, ShallIdentifyCloths)
{
    m_laundrySensor.AddLaundry(LaundrySensor::LaundryLevel::L1);
    m_iut.Run();
    EXPECT_TRUE(m_indicator.IsLaundryAvailableIndicatorOn());
}

TEST_F(TestWashingMachineStates, ShallIndicateLaundryWeight)
{
    m_laundrySensor.AddLaundry(LaundrySensor::LaundryLevel::L1);
    m_iut.Run();
    EXPECT_EQ(LaundrySensor::LaundryLevel::L1, m_indicator.GetLaundryWeightLevel());

    m_laundrySensor.AddLaundry(LaundrySensor::LaundryLevel::L2);
    m_iut.Run();
    EXPECT_EQ(LaundrySensor::LaundryLevel::L2, m_indicator.GetLaundryWeightLevel());
}

TEST_F(TestWashingMachineStates, ShallIndicateRecommendedWaterNone)
{
    m_iut.Run();
    EXPECT_EQ(Indicator::WaterLevel::NONE, m_indicator.GetRecommendedWaterLevel());
}

TEST_F(TestWashingMachineStates, ShallIndicateRecommendedWaterLevel1)
{
    m_laundrySensor.AddLaundry(LaundrySensor::LaundryLevel::L1);
    m_iut.Run();
    EXPECT_EQ(Indicator::WaterLevel::L1, m_indicator.GetRecommendedWaterLevel());
}

TEST_F(TestWashingMachineStates, ShallStartWaterAfterStartIsPressed)
{
    m_laundrySensor.AddLaundry(LaundrySensor::LaundryLevel::L1);
    m_iut.Run();

    m_userInputs.PressStart();
    m_iut.Run();
    EXPECT_STREQ("<WaterStarted-SlowSpin>", m_washCycle.GetSequence().c_str());
}

TEST_F(TestWashingMachineStates, ShallIndicateWaterLevel)
{
    m_laundrySensor.AddLaundry(LaundrySensor::LaundryLevel::L1);
    m_iut.Run();

    m_userInputs.PressStart();
    m_iut.Run();
    EXPECT_EQ(Indicator::WaterLevel::NONE, m_indicator.GetActualWaterLevel());

    m_waterSensor.SetLevel(Indicator::WaterLevel::L1);
    EXPECT_EQ(Indicator::WaterLevel::L1, m_indicator.GetActualWaterLevel())
}


// TEST_F(TestWashingMachineStates, ShallStartWashingCycleOnceTheWaterLevelReachedTheRecommendedLevel)
// {
//     m_laundrySensor.AddLaundry(LaundrySensor::LaundryLevel::L1);
//     m_iut.Run();
// 
//     m_userInputs.PressStart();
//     m_iut.Run();
// 
//     m_washCycle.WaterLevelReached();
//     m_iut.Run();
// 
//     EXPECT_STREQ("<WaterStarted-SlowSpin><WashAlgoStarted>", m_washCycle.GetSequence().c_str());
// }
