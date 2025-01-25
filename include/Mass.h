#ifndef MASS_H_
#define MASS_H_
#include <ngl/Vec3.h>

// This class represents the methods and attributes that a point mass have in the simulation.

class Mass {

    public:
        Mass() = default; // Default constructor

        // Parametrized constructors
        Mass(ngl::Vec3 initPos, ngl::Vec3 initVel, ngl::Vec3 pos, ngl::Vec3 vel, float mass, float size, bool isFixed); 
        Mass(ngl::Vec3 iniPos, bool isFix);

        ~Mass() = default; // Default destructor
       
        // Getter methods 
       ngl::Vec3 getPosition();
        ngl::Vec3 getVelocity();
        ngl::Vec3 getInitPosition();
        ngl::Vec3 getInitVelocity();
        float getMass();
        float getSize();
        bool getIsFixed();

        // Setter methods
        void setPosition(const ngl::Vec3 &pos);
        void setVelocity(const ngl::Vec3 &vel);
        void setMass(const float &mass);

        // Methods
        void updateState(ngl::Vec3 newPos, ngl::Vec3 newVel); // Assign a new position and a new velocity to m_position and m_velocity     
        void resetState(); // Assign to m_position and m_velocity the values to 0

    private:
        // Attributes
        ngl::Vec3 m_initPosition;                       // Initial position 
        ngl::Vec3 m_initVelocity = {0.0f, 0.0f, 0.0f};  // Initial velocity
        ngl::Vec3 m_position = m_initPosition;          // Position over the simulation time 
        ngl::Vec3 m_velocity = m_initVelocity;          // Velocity over the simulation time
        float m_mass = 1.0f;                            // Mass
        float m_size = 7.0f;                            // Size 
        bool m_isFixed = false;                         // Indicates if the mass is fixed (static in initial position)
        
};
#endif
