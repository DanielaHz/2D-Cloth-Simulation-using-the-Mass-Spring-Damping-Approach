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
        // Initialization method
        void initCloth(int numMassWidth, int numMassHeight, float spacing); // Set up the initial position of the point masses and the springs in the system

        // Create methods
        void createMass(int width, int height, float spacing); // Create the masses in the system and store them in m_massInSystem
        void createSpringConnections(int numMassWidth, int numMassHeigth); // Identify the spring connections with the masses in the system and populate the uniqueConnections and allConnections maps
        void createSpring(float spacing); // Create springs based on the given spacing

        // Print methods
        void printConnectionsMap(); // Print the uniqueConnection map
        void printAllConnections(); // Print the allConnections map 
        int printTotalSpings(); // Print the total springs in the system taking in count the uniqueConnection map

        // Drawing methods
        void drawCloth(); // Draw the cloth by calling drawMass and drawSpring
        void drawMass(); // Populate the massVAO to draw masses
        void drawSpring(); // Populate the springVAO to draw springs

        // Forces methods
        ngl::Vec3 calcGravityForce(ngl::Vec3 gravity, float mass); // Calculate the gravity force
        ngl::Vec3 calcDragForce(ngl::Vec3 velocity, float drag); // Calculate the drag force
        ngl::Vec3 calcSpringForce(float distance, float stiffness, ngl::Vec3 direction); // Calculate the spring force
        ngl::Vec3 calcDampingForce(ngl::Vec3 velocity, float damping); // Calculate the damping force
        ngl::Vec3 calcFinalForce(ngl::Vec3 gravity, ngl::Vec3 drag, ngl::Vec3 spring, ngl::Vec3 damping); // Calculate the final force from various forces
        void evaluateForces();// Calculate and update the final force acting on each mass in the system

        // Interactive Forces methods
        // ngl::Vec3 applyLeftClickForce(float forceRadius, float forceMaginitude); // this force its applyied in the z position when the user put left click 
        // ngl:Vec3 applyRightClickForce // this force find the nearest point where the point the user click and pull the point to that position 

        // Integration methods
        void requestNewState(float t, float dt); // Update the state (position and velocity) of each mass based on the current time and time step 

        // Getter methods (Mostly created to test the cloth class in the ClothTest.cpp)
        std::vector<std::shared_ptr<Mass>> getMassInSystem();
        std::vector<Spring> getSpringInSystem();
        std::map<int, std::vector<int>> getUniqueConnections();
        std::map<int, std::vector<int>> getAllConnections();
        std::map<int, ngl::Vec3> getFinalForces();
        float getDrag();
        ngl::Vec3 getGravity();

    private: 
        // Attributes
        int m_windowWidth = 1240;                               // Window width useful to position the first mass point row
        ngl::Vec3 m_gravity = {0.0f, -9.80f, 0.0f};             // Gravity constant
        float m_drag = 0.1f;                                    // Drag constant (usually has a value between 0.01 to 0.5)
        float m_damping = 0.5f;                                 // Dampign constant (usually has a value between 0.1 to 1.0)
        float m_structuralStiffness = 8.0f;                     // Stiffness constant for structural springs
        float m_shearStiffness = 0.0f;                          // Stiffness constant for shear springs
        float m_bendStiffness = 0.0f;                           // Stiffness constant for bend springs
        std::vector<std::shared_ptr<Mass>> m_massInSystem;      // Vector that contains all the masses in the system. Masses are positioned from right to left and top to bottom 
        std::vector<Spring> m_springInSystem;                   // Vector that contains all the springs in the system. This vector follows the connections provided by the uniqueConnections map
        std::map<int, std::vector<int>> m_uniqueConnections;    // Map that contains the unique connections of masses in the system, depending on the type of spring that connects the respective masses. The key represents the index of the masses, and the value is a vector with the indices of the connected masses. It is unique because it checks if the connection 1-2 exists; when at 2-1, it does not need to be created
        std::map<int, std::vector<int>> m_allConnections;       // Map that stores all the possible connections. It helps to debug the connections created
        std::map<int, ngl::Vec3> m_finalForces;                 // Map that stores the final force acting over the mass. The key is the index of the mass and the value the final force
        std::unique_ptr<ngl::AbstractVAO> m_massVAO;            // Vertex array to draw the masses 
        std::unique_ptr<ngl::AbstractVAO> m_springVAO;          // Vertex array to draw the springs
};

#endif