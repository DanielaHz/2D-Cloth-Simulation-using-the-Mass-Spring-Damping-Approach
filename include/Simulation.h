#ifndef SIMULATION_H_
#define SIMULATION_H_

#include "Cloth.h"
#include <chrono>


class Simulation {
public:
    Simulation (int width, int height, float spacing);
    void initialize();
    void render();
    void update(float deltaTime);
    void start();
    void simulationLoop();
private:
    Cloth m_cloth;
    std::chrono::steady_clock::time_point m_lastTime;
    float m_time;

};

#endif