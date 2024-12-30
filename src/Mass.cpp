#include "Mass.h"

Mass::Mass(ngl::Vec3 initPos, ngl::Vec3 initVel, ngl::Vec3 pos, ngl::Vec3 vel, float mass, float size, bool isFixed)
    : initPosition{initPos}, initVelocity{initVel}, position{pos}, velocity{vel}, mass{mass}, size{size}, isFixed{isFixed} {};

void Mass::updateState(ngl::Vec3 newPos, ngl::Vec3 newVel)
{
    position.set(newPos);
    velocity.set(newVel);
}

void Mass::resetState()
{
    position.set({0.0f, 0.0f,0.0f});
    velocity.set({0.0f, 0.0f, 0.0f});
}