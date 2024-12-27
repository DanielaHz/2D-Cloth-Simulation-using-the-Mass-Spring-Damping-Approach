#ifndef MASS_H_
#define MASS_H_
#include <ngl/Vec3.h>
class Mass {
    public:
        ngl::Vec3 position;
        ngl::Vec3 velocity;
        float mass = 1.0f; 
        float size = 5.0f;

        Mass () = default;
        ~Mass () = default; 
};
#endif
