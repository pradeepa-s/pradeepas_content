#include "gtest/gtest.h"
#include "washing_machine.hpp"
#include "indicator.hpp"
#include "laundry_sensor.hpp"

class TestWashingMachineStates: public ::testing::Test
{
protected:
    TestWashingMachineStates():
        m_laundrySensor(), m_indicator(),
        m_iut(m_laundrySensor, m_indicator)
    {
    }

protected:
    LaundrySensor m_laundrySensor;
    Indicator m_indicator;
    WashingMachine m_iut;
};

TEST_F(TestWashingMachineStates, ShallIdentifyNoCloths)
{
    m_iut.Run();
    EXPECT_FALSE(m_indicator.GetClothIndicator());
}

TEST_F(TestWashingMachineStates, ShallIdentifyCloths)
{
    m_laundrySensor.AddLaundry();
    m_iut.Run();
    EXPECT_TRUE(m_indicator.GetClothIndicator());
}
