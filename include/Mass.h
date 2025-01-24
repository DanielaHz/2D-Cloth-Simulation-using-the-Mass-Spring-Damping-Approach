#ifndef MASS_H_
#define MASS_H_
#include <ngl/Vec3.h>

class Mass {

    public:
        Mass() = default;
        Mass(ngl::Vec3 initPos, ngl::Vec3 initVel, ngl::Vec3 pos, ngl::Vec3 vel, float mass, float size, bool isFixed);
        Mass(ngl::Vec3 iniPos, bool isFix);
        ~Mass() = default;
        ngl::Vec3 getPosition();
        ngl::Vec3 getVelocity();
        ngl::Vec3 getInitPosition();
        ngl::Vec3 getInitVelocity();
        float getMass();
        float getSize();
        bool getIsFixed();
        void setPosition(const ngl::Vec3 &pos);
        void setVelocity(const ngl::Vec3 &vel);
        void setMass(const float &mass);
        void updateState(ngl::Vec3 newPos, ngl::Vec3 newVel);      
        void resetState();

    private:
        ngl::Vec3 m_initPosition;
        ngl::Vec3 m_initVelocity = {0.0f, 0.0f, 0.0f};
        ngl::Vec3 m_position = m_initPosition;
        ngl::Vec3 m_velocity = m_initVelocity;
        float m_mass = 1.0f; 
        float m_size = 5.0f;
        bool m_isFixed = false;
        
};
#endif
