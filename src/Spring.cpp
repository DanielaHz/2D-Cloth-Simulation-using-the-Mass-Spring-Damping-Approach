#include "Spring.h"

Spring::Spring(float initLen, float finalLen, float stiffness, std::shared_ptr<Mass> m1, std::shared_ptr<Mass> m2)
    : initLength{initLen}, finalLength{finalLen}, stiffness{stiffness}, mass1{m1}, mass2{m2} {}

ngl::Vec3 Spring::getMassPosition(std::shared_ptr<Mass> m)
{
    float x = m->position.m_x;
    float y = m->position.m_y;
    float z = m->position.m_z;
    return {x, y, z};
}

float Spring::calculateFinalLength( std::shared_ptr<Mass> m1, std::shared_ptr<Mass> m2)
{
    ngl::Vec3 pos1 = getMassPosition(m1);
    ngl::Vec3 pos2 = getMassPosition(m2);

    ngl::Vec3 dif = pos2 - pos1;

    return dif.length();

}
