#ifndef CLOTH_H_
#define CLOTH_H_
#include <ngl/Vec3.h>
#include "Mass.h"
#include "Spring.h"
#include <vector>

class Cloth {
public:
    // temporary value for window width and height -> should be changed with a pointer to reference the window in NGLScene
    int windowWidth = 1240;
    int windowHeight = 720;

    std::vector<Mass> massInSystem;
    std::vector<Spring> springInSystem;
    ngl::Vec3 gravity = {0.0f, -9.8f, 0.0f};
    // void initCloth(int Width, int Height, float spacing); // setup the initial position of the particles  and the inital position of the springs
    void placeMass(int width, int height, float spacing); // Created to modularize the responsibility of initCloth
    //void placeSpring(); Created to modularize the responsibility of initCloth
    // void drawCloth();
};

#endif