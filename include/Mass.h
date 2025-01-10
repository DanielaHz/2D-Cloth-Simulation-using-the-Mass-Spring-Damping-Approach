#ifndef MASS_H_
#define MASS_H_
#include <ngl/Vec3.h>

class Mass {
    public:
        ngl::Vec3 initPosition;
        ngl::Vec3 initVelocity = {0.0f, 0.0f, 0.0f};
        ngl::Vec3 position = initPosition;
        ngl::Vec3 velocity = initVelocity;
        float mass = 1.0f; 
        float size = 5.0f;
        bool isFixed = false;

        Mass() = default;
        Mass(ngl::Vec3 initPos, ngl::Vec3 initVel, ngl::Vec3 pos, ngl::Vec3 vel, float mass, float size, bool isFixed);
        Mass(ngl::Vec3 iniPos, bool isFix);
        ~Mass() = default;

        void updateState(ngl::Vec3 newPos, ngl::Vec3 newVel);      
        void resetState();
};
#endif
