#ifndef SIMULATION_H_
#define SIMULATION_H_
#include "Cloth.h"
#include <chrono>

// This class handles the simulation of a particle system, using the Cloth class to represent the particle mesh

class Simulation {

    public:
        // Default constructor
        // * @param numMassWidth Total masses in the width.
        // * @param numMassHeight Total masses in the height.
        // * @param spacing Space between masses position.
        Simulation (int numMassWidth, int numMassHeight, float spacing);

        // Methods
        void initialize();
        void render(); 
        void update(float deltaTime);
        void start();
        // void simulationLoop();
        void applyLeftClick(ngl::Vec3 nglClickPosition);
        
    private:
    Cloth m_cloth;                                          // Point mass mesh used in the simulation
    std::chrono::steady_clock::time_point m_lastTime;       // Last recorded time
    float m_time;                                           // Accumulated simulation time
};

#endif