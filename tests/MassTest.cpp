#include <gtest/gtest.h>
#include "Mass.h"

TEST(Mass, DefaultConstructor)
{
    Mass m;
    EXPECT_FLOAT_EQ(m.mass, 1.0f);  
    EXPECT_FLOAT_EQ(m.size, 5.0f);
    EXPECT_FALSE(m.isFixed);
}

TEST(Mass, ParametrizedConstructor)
{
    ngl::Vec3 initPos{1.0f, 2.0f, 3.0f};
    ngl::Vec3 initVel{0.1f, 0.2f, 0.3f};
    ngl::Vec3 pos{4.0f, 5.0f, 6.0f};
    ngl::Vec3 vel{0.4f, 0.5f, 0.6f};
    float mass = 2.0f;
    float size = 10.0f;
    bool isFixed = true;

    Mass m(initPos, initVel, pos, vel, mass, size, isFixed);

    EXPECT_EQ(m.initPosition, initPos);
    EXPECT_EQ(m.initVelocity, initVel);
    EXPECT_EQ(m.position, pos);
    EXPECT_EQ(m.velocity, vel);
    EXPECT_FLOAT_EQ(m.mass, mass);
    EXPECT_FLOAT_EQ(m.size, size);
    EXPECT_TRUE(m.isFixed);
}