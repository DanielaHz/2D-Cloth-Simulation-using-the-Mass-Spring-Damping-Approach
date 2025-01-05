#include "Simulation.h"

Simulation::Simulation(int width, int height, float spacing)
{
    m_cloth.initCloth(width, height, spacing);
}

void Simulation::render()
{
    m_cloth.drawCloth();
}