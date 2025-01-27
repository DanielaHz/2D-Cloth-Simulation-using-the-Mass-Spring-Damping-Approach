#include "Simulation.h"

Simulation::Simulation(int numMassWidthdth, int numMassHeight, float spacing)
    : m_lastTime(std::chrono::steady_clock::now()), m_time(0.0f) 
{
    // Set the forces constants and enable the springs here!! 
    m_cloth.setGravity({0.0f, -9.80f, 0.0f});
    m_cloth.setDrag(0.1f);
    m_cloth.setDamping(0.5f);
    m_cloth.setEnableStructuralSprings();
    m_cloth.setStructuralStiffness(8.0f);
    m_cloth.initCloth(numMassWidthdth, numMassHeight, spacing);
}

void Simulation::initialize()
{
    m_time = 0.0f;
}

void Simulation::update(float deltaTime)
{
    m_cloth.evaluateForces();
    m_cloth.requestNewState(m_time , deltaTime);
    m_time += deltaTime;
}

void Simulation::render()
{
    m_cloth.drawCloth();
}

void Simulation::applyLeftClick(ngl::Vec3 nglClickPosition)
{
    m_cloth.applyLeftClickForce(nglClickPosition);
}
