#ifndef CLOTH_H_
#define CLOTH_H_
#include <ngl/Vec3.h>
#include "Mass.h"
#include "Spring.h"
#include <vector>
#include <map>
#include <utility> 

class Cloth {
public:
    // temporary value for window width and height -> should be changed with a pointer to reference the window in NGLScene
    int windowWidth = 1240;
    int windowHeight = 720;

    std::vector<Mass> massInSystem;
    std::vector<Spring> springInSystem;
    std::map<std::pair<int, int>, std::vector<std::pair<int, int>>> connections;
    ngl::Vec3 gravity = {0.0f, -9.8f, 0.0f};

    void initCloth(int width, int height, float spacing); // setup the initial position of the particles  and the inital position of the springs
    void createMass(int width, int height, float spacing); // Created to modularize the responsibility of initCloth
    void createSpringConnections(int numMassWidth, int numMassHeigth); // function created to identify the spring conecctions with the mass in the system
    void printConnecitonsMap ();
    void createSpring();
    // void drawCloth();
};

#endif