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

    void RunUntilWaterStarts()
    {
        m_laundrySensor.AddLaundry(ILaundrySensor::LaundryLevel::L1);
        m_userInputs.PressStart();
        RunEnough();
        m_userInputs.Release();
    }

    void TriggerError(IWashingCycles::Error error)
    {
        m_washCycle.ReportError(error);
        RunEnough();
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

TEST_F(TestWashingMachineStates, ShallIndicateWaterError)
{
    RunUntilWaterStarts();
    TriggerError(IWashingCycles::Error::NO_WATER_FLUX);
    EXPECT_EQ(IIndicator::MachineState::ERROR, m_indicator.GetState());
}

TEST_F(TestWashingMachineStates, ShallStartWashingCycleOnceTheWaterLevelReachedTheRecommendedLevel)
{
    m_laundrySensor.AddLaundry(ILaundrySensor::LaundryLevel::L2);
    m_userInputs.PressStart();
    m_waterSensor.SetLevel(IWaterSensor::WaterLevel::L2);

    RunEnough();

    EXPECT_STREQ("<WaterStarted-SlowSpin><WaterStopped><WashAlgoStarted>",
            m_washCycle.GetSequence().c_str());
    EXPECT_EQ(IIndicator::MachineState::WASHING, m_indicator.GetState());
}

TEST_F(TestWashingMachineStates, ShallStartRinseAlgorithmAfterWash)
{
    m_laundrySensor.AddLaundry(ILaundrySensor::LaundryLevel::L2);
    m_userInputs.PressStart();
    m_waterSensor.SetLevel(IWaterSensor::WaterLevel::L2);
    RunEnough();

    m_washCycle.FinishWash();
    RunEnough();
    EXPECT_STREQ("<WaterStarted-SlowSpin><WaterStopped><WashAlgoStarted><RinseStarted>",
            m_washCycle.GetSequence().c_str());
    EXPECT_EQ(IIndicator::MachineState::RINSE, m_indicator.GetState());
}

TEST_F(TestWashingMachineStates, ShallStartSpinAlgorithmAfterRinse)
{
    m_laundrySensor.AddLaundry(ILaundrySensor::LaundryLevel::L2);
    m_userInputs.PressStart();
    m_waterSensor.SetLevel(IWaterSensor::WaterLevel::L2);
    RunEnough();
    m_washCycle.FinishWash();
    RunEnough();

    m_washCycle.FinishRinse();
    RunEnough();

    EXPECT_STREQ("<WaterStarted-SlowSpin><WaterStopped><WashAlgoStarted><RinseStarted><SpinStarted>",
            m_washCycle.GetSequence().c_str());
    EXPECT_EQ(IIndicator::MachineState::SPIN, m_indicator.GetState());
}

TEST_F(TestWashingMachineStates, ShallIndicateDoneAfterSpin)
{
    m_laundrySensor.AddLaundry(ILaundrySensor::LaundryLevel::L2);
    m_userInputs.PressStart();
    m_waterSensor.SetLevel(IWaterSensor::WaterLevel::L2);
    RunEnough();
    m_washCycle.FinishWash();
    RunEnough();
    m_washCycle.FinishRinse();
    RunEnough();

    m_washCycle.FinishSpin();
    RunEnough();
    EXPECT_STREQ("<WaterStarted-SlowSpin><WaterStopped><WashAlgoStarted><RinseStarted><SpinStarted><SpinStopped>",
            m_washCycle.GetSequence().c_str());
    EXPECT_EQ(IIndicator::MachineState::DONE, m_indicator.GetState());
}

TEST_F(TestWashingMachineStates, ShallIndicateNoLaundryAfterLaundryIsTakenFromMachine)
{
    m_laundrySensor.AddLaundry(ILaundrySensor::LaundryLevel::L2);
    m_userInputs.PressStart();
    m_waterSensor.SetLevel(IWaterSensor::WaterLevel::L2);
    RunEnough();
    m_washCycle.FinishWash();
    RunEnough();
    m_washCycle.FinishRinse();
    RunEnough();
    m_washCycle.FinishSpin();
    RunEnough();

    m_laundrySensor.AddLaundry(ILaundrySensor::LaundryLevel::NONE);
    m_waterSensor.SetLevel(IWaterSensor::WaterLevel::NONE);
    RunEnough();
    EXPECT_FALSE(m_indicator.IsLaundryAvailableIndicatorOn());
    EXPECT_EQ(IIndicator::LaundryLevel::NONE, m_indicator.GetLaundryWeightLevel());
    EXPECT_EQ(IIndicator::WaterLevel::NONE, m_indicator.GetRecommendedWaterLevel());
    EXPECT_EQ(IIndicator::WaterLevel::NONE, m_indicator.GetActualWaterLevel());
    EXPECT_FALSE(m_indicator.IsLaundryAvailableIndicatorOn());
}

TEST_F(TestWashingMachineStates, ShallStartWaterIfUserFixedWaterError)
{
    RunUntilWaterStarts();
    TriggerError(IWashingCycles::Error::NO_WATER_FLUX);

    m_userInputs.PressStart();
    RunEnough();
    EXPECT_STREQ("<WaterStarted-SlowSpin><ErrorCleared><WaterStarted-SlowSpin>", m_washCycle.GetSequence().c_str());
}
//
// TEST_F(TestWashingMachineStates, ShallIndicateErrorsDuringWashingLaundry)
// {
//     EXPECT_TRUE(false);
// }
//
// TEST_F(TestWashingMachineStates, ShallContinueTheWashIfUserClearedWashingError)
// {
//     EXPECT_TRUE(false);
// }
//
// TEST_F(TestWashingMachineStates, ShallIndicateErrorsDuringRinsingLaundry)
// {
//     EXPECT_TRUE(false);
// }
//
// TEST_F(TestWashingMachineStates, ShallContinueTheWashIfUserClearedRinsingError)
// {
//     EXPECT_TRUE(false);
// }
//
// TEST_F(TestWashingMachineStates, ShallIndicateErrorsDuringSpin)
// {
//     EXPECT_TRUE(false);
// }
//
// TEST_F(TestWashingMachineStates, ShallStopTheWashOperationIfUserPressCancelWhenInError)
// {
//     EXPECT_TRUE(false);
// }
