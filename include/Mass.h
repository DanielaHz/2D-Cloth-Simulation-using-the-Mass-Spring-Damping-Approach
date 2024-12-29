#ifndef MASS_H_
#define MASS_H_
#include <ngl/Vec3.h>

class Mass {
    public:
        ngl::Vec3 initPosition;
        ngl::Vec3 initVelocity;
        ngl::Vec3 position;
        ngl::Vec3 velocity;
        float mass = 1.0f; 
        float size = 5.0f;
        bool isFixed = false;

        Mass() = default;
        Mass(ngl::Vec3 initPos, ngl::Vec3 initVel, ngl::Vec3 pos, ngl::Vec3 vel, float mass, float size, bool isFixed);
        ~Mass() = default;

        void updateState(ngl::Vec3 newPos, ngl::Vec3 newVel);      
};
#endif
