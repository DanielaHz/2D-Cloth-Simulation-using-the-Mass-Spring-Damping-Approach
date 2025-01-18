#include "Simulation.h"

Simulation::Simulation(int width, int height, float spacing)
    : m_lastTime(std::chrono::steady_clock::now()), m_time(0.0f) 
{
    m_cloth.initCloth(width,height, spacing);
}

void Simulation::initialize()
{
    // should initalize the forces constants here and not declare it in cloth?
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
    simulationLoop();
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