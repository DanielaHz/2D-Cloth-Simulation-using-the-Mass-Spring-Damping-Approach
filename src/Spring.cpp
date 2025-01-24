#include "Spring.h"

Spring::Spring(float restLen, float currentLen, float stiffness, std::shared_ptr<Mass> m1, std::shared_ptr<Mass> m2)
    : m_restLength{restLen}, m_currentLength{currentLen}, m_stiffness{stiffness}, m_mass1{m1}, m_mass2{m2} {}

Spring::Spring(float restLen, float stiff, std::shared_ptr<Mass> m1, std::shared_ptr<Mass> m2)
    : m_restLength{restLen}, m_stiffness{stiff}, m_mass1{m1}, m_mass2{m2} {}

ngl::Vec3 Spring::getMassPosition(std::shared_ptr<Mass> m)
{
    float x = m->getPosition().m_x;
    float y = m->getPosition().m_y;
    float z = m->getPosition().m_z;
    return {x, y, z};
}

float Spring::calculateCurrentLength( std::shared_ptr<Mass> m1, std::shared_ptr<Mass> m2)
{
    ngl::Vec3 pos1 = getMassPosition(m1);
    ngl::Vec3 pos2 = getMassPosition(m2);

    ngl::Vec3 dis = pos2 - pos1;

    return dis.length();
}

float Spring::getRestLength() {return m_restLength;}

float Spring::getCurrentLength() {return m_currentLength;}

float Spring::getStiffness() {return m_stiffness;}

std::shared_ptr<Mass> Spring::getMass1() {return m_mass1;}

std::shared_ptr<Mass> Spring::getMass2() {return m_mass2;}

void Spring::setStiffness (const float &stiff) {m_stiffness = stiff;}

void Spring::setRestLength (const float &len) {m_restLength = len;}