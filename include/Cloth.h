#ifndef CLOTH_H_
#define CLOTH_H_
#include <ngl/Vec3.h>
#include "Mass.h"
#include "Spring.h"
#include <vector>
#include <map>
#include <utility> 
#include <iostream>
#include <set>
#include <ngl/AbstractVAO.h>
#include <ngl/VAOFactory.h>
#include <memory>
#include "TimeIntegrator.h"

class Cloth {
public:
    // temporary value for window width and height -> should be changed with a pointer to reference the window in NGLScene
    int windowWidth = 1240;
    int windowHeight = 720;

    std::vector<std::shared_ptr<Mass>> massInSystem;
    std::vector<Spring> springInSystem;
    std::map<int, std::vector<int>> uniqueConnections;
    std::map<int, std::vector<int>> allConnections; 
  
    ngl::Vec3 gravity = {0.0f, -9.81f, 0.0f};
    float drag = 0.05f; // drag constant is a value between 0.01 to 0.5
    std::map<int, ngl::Vec3> finalForces; // contain the index of the mass and the final force value acting over the mass
   
    void initCloth(int width, int height, float spacing); // setup the initial position of the particles  and the inital position of the springs
    void createMass(int width, int height, float spacing); // Created to modularize the responsibility of initCloth
    void createSpringConnections(int numMassWidth, int numMassHeigth); // function created to identify the spring conecctions with the mass in the system( unique connections now)
    void printConnectionsMap();
    void printAllConnections();
    void createSpring(float spacing);
    void drawCloth(); // call the function to draw the mass and the springs
    void drawMass();
    void drawSpring(); 

    // Simulation part, calculate forces and calling the RK4 time integrator
    ngl::Vec3 calcGravityForce(ngl::Vec3 gravity, float mass); 
    ngl::Vec3 calcDragForce(ngl::Vec3 velocity, float drag);
    ngl::Vec3 calcSpringForce(float distance, float stiffness, ngl::Vec3 direction);
    ngl::Vec3 calcFinalForce(ngl::Vec3 gravity, ngl::Vec3 drag, ngl::Vec3 spring);
    void evaluateForces();// calculate forces , calculate final one and request new state and update new state
    void requestNewState(float t, float dt); //  give me the new state(position and velocity) per mass
private: 
    std::unique_ptr<ngl::AbstractVAO> m_massVAO;
    std::unique_ptr<ngl::AbstractVAO> m_springVAO;
};
#endif