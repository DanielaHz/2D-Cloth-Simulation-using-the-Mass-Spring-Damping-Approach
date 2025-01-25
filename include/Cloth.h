#ifndef CLOTH_H_
#define CLOTH_H_
#include <ngl/Vec3.h>
#include "Mass.h"
#include "Spring.h"
#include "TimeIntegrator.h"
#include <ngl/AbstractVAO.h>
#include <ngl/VAOFactory.h>
#include <vector>
#include <map>
#include <utility> 
#include <iostream>
#include <set>
#include <memory>

class Cloth {

    public:
        void initCloth(int numMassWidth, int numMassHeight, float spacing); // setup the initial position of the point mass and the springs in the system.
        void createMass(int width, int height, float spacing); // Create 
        void createSpringConnections(int numMassWidth, int numMassHeigth); // function created to identify the spring conecctions with the mass in the system( unique connections now)
        void printConnectionsMap();
        void printAllConnections();
        void createSpring(float spacing);
        void drawCloth(); // call the function to draw the mass and the springs
        void drawMass();
        void drawSpring(); 
        ngl::Vec3 calcGravityForce(ngl::Vec3 gravity, float mass); 
        ngl::Vec3 calcDragForce(ngl::Vec3 velocity, float drag);
        ngl::Vec3 calcSpringForce(float distance, float stiffness, ngl::Vec3 direction);
        ngl::Vec3 calcDampingForce(ngl::Vec3 velocity, float damping);
        ngl::Vec3 calcFinalForce(ngl::Vec3 gravity, ngl::Vec3 drag, ngl::Vec3 spring, ngl::Vec3 damping);
        void evaluateForces();// calculate forces , calculate final one and request new state and update new state
        void requestNewState(float t, float dt); //  give me the new state(position and velocity) per mass
        int printTotalSpings();
        // ngl::Vec3 applyLeftClickForce(float forceRadius, float forceMaginitude);

        // get created to access from the cloth unit test
        std::vector<std::shared_ptr<Mass>> getMassInSystem();
        std::vector<Spring> getSpringInSystem();
        std::map<int, std::vector<int>> getUniqueConnections();
        std::map<int, std::vector<int>> getAllConnections();
        std::map<int, ngl::Vec3> getFinalForces();
        float getDrag();
        ngl::Vec3 getGravity();

    private: 
        int m_windowWidth = 1240;
        ngl::Vec3 m_gravity = {0.0f, -9.80f, 0.0f};
        float m_drag = 0.1f; // drag constant is a value between 0.01 to 0.5
        std::vector<std::shared_ptr<Mass>> m_massInSystem;
        std::vector<Spring> m_springInSystem;
        std::map<int, std::vector<int>> m_uniqueConnections;
        std::map<int, std::vector<int>> m_allConnections;
        std::map<int, ngl::Vec3> m_finalForces; // contain the index of the mass and the final force value acting over the mass 
        std::unique_ptr<ngl::AbstractVAO> m_massVAO;
        std::unique_ptr<ngl::AbstractVAO> m_springVAO;
};

#endif