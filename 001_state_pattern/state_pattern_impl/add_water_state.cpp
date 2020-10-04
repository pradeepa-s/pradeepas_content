#include "add_water_state.hpp"
#include "Istate_control.hpp"
#include "Iwater_sensor.hpp"
#include "Iwashing_cycles.hpp"

AddWaterState::AddWaterState(IWashingMachineContext& stateControl, IWaterSensor& waterSensor,
        IWashingCycles& washCycle):
    m_context(stateControl),
    m_waterSensor(waterSensor),
    m_washCycles(washCycle)
{}

void AddWaterState::Run()
{
    if (RecommendedWaterLevelReached())
    {
        m_washCycles.StopWater();
        m_context.ChangeState(IWashingMachineState::State::WASH);
    }
}

void AddWaterState::Reset()
{
    m_washCycles.StartWater();
}

bool AddWaterState::RecommendedWaterLevelReached()
{
    return m_context.GetWaterLevelTarget() == m_waterSensor.GetLevel();
}
