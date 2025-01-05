#ifndef SIMULATION_H_
#define SIMULATION_H_

# include "Cloth.h"

// for the moment his class only implement the functions created in Cloth as draw and init
class Simulation {
public:
    Simulation (int width, int height, float spacing);
    void render();
private:
    Cloth m_cloth;
};

#endif