#include "Simulation.h"

Simulation::Simulation(int numMassWidthdth, int numMassHeight, float spacing)
    : m_lastTime(std::chrono::steady_clock::now()), m_time(0.0f) 
{
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

void Simulation::start()
{
    m_lastTime = std::chrono::steady_clock::now();
    // simulationLoop();
}

// void Simulation::simulationLoop() {
//     while (true) {
//         auto currentTime = std::chrono::steady_clock::now();
//         std::chrono::duration<float> elapsedTime = currentTime - m_lastTime;
//         float deltaTime = elapsedTime.count();

//         if (deltaTime >= 0.01f) 
//         {
//             update(0.01f);
//             render();
//             m_lastTime = currentTime;
//         }
//     }
// }

void Simulation::applyLeftClick(ngl::Vec3 nglClickPosition)
{
    m_cloth.applyLeftClickForce(nglClickPosition);
}
