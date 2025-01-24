#include "Mass.h"

Mass::Mass(ngl::Vec3 initPos, ngl::Vec3 initVel, ngl::Vec3 pos, ngl::Vec3 vel, float mass, float size, bool isFixed)
    : m_initPosition{initPos}, m_initVelocity{initVel}, m_position{pos}, m_velocity{vel}, m_mass{mass}, m_size{size}, m_isFixed{isFixed} {};

Mass::Mass(ngl::Vec3 initPos, bool isFix)
    : m_initPosition{initPos}, m_isFixed{isFix} {};

void Mass::updateState(ngl::Vec3 newPos, ngl::Vec3 newVel)
{
    m_position.set(newPos);
    m_velocity.set(newVel);
}

void Mass::resetState()
{
    m_position.set({0.0f, 0.0f,0.0f});
    m_velocity.set({0.0f, 0.0f, 0.0f});
}

ngl::Vec3 Mass::getPosition() {return m_position;}

ngl::Vec3 Mass::getVelocity() {return m_velocity;}

ngl::Vec3 Mass::getInitPosition() {return m_initPosition;}

ngl::Vec3 Mass::getInitVelocity() {return m_initVelocity;}

float Mass::getMass() {return m_mass;}

float Mass::getSize() {return m_size;}

bool Mass::getIsFixed() {return m_isFixed;}

void Mass::setPosition(const ngl::Vec3 &pos) {m_position = pos;}

void Mass::setVelocity(const ngl::Vec3 &vel) {m_velocity = vel;}

void Mass::setMass(const float &mass) {m_mass = mass;}
