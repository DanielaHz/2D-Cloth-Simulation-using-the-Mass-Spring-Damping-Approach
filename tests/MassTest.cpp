#include <gtest/gtest.h>
#include "Mass.h"

TEST(Mass, DefaultConstructor)
{
    Mass m;
    EXPECT_FLOAT_EQ(m.getMass(), 1.0f);  
    EXPECT_FLOAT_EQ(m.getSize(), 7.0f);
    EXPECT_FALSE(m.getIsFixed());
}

TEST(Mass, ParametrizedConstructor)
{
    // test values mass 1
    ngl::Vec3 initPos{1.0f, 2.0f, 0.0f};
    ngl::Vec3 initVel{0.1f, 0.2f, 0.0f};
    ngl::Vec3 pos = initPos;
    ngl::Vec3 vel = initVel;
    float mass = 2.0f;
    float size = 10.0f;
    bool isFixed = true;

    // creating the mass 1 to test
    Mass m(initPos, initVel, pos, vel, mass, size, isFixed);

    EXPECT_EQ(m.getInitPosition(), initPos);
    EXPECT_EQ(m.getInitVelocity(), initVel);
    EXPECT_EQ(m.getPosition(), pos);
    EXPECT_EQ(m.getVelocity(), vel);
    EXPECT_FLOAT_EQ(m.getMass(), mass);
    EXPECT_FLOAT_EQ(m.getSize(), size);
    EXPECT_TRUE(m.getIsFixed());

    //////////////////////////////////////////////////////

    // test values mass 2
    ngl::Vec3 initPosition = {5.0f, 0.0f, 0.0f};
    ngl::Vec3 initVelocity = {0.0f, 0.0f, 0.0f};
    ngl::Vec3 position = initPosition;
    ngl::Vec3 velocity = initVelocity;
    float mass2 = 1.0f; 
    float size2 = 7.0f;

    // creating the mass 2 to test
    Mass m2(ngl::Vec3 {5.0f, 0.0f, 0.0f}, isFixed = true);

    EXPECT_EQ(m2.getInitPosition(), initPosition);
    EXPECT_EQ(m2.getInitVelocity(), initVelocity);
    EXPECT_EQ(m2.getPosition(), position);
    EXPECT_EQ(m2.getVelocity(), velocity);
    EXPECT_FLOAT_EQ(m2.getMass(), mass2);
    EXPECT_FLOAT_EQ(m2.getSize(), size2);
    EXPECT_TRUE(m2.getIsFixed());
}

TEST(Mass, updateState)
{   
    // Initial state of the mass m
    Mass m (ngl::Vec3 {4.0f, 5.0f, 0.0f}, ngl::Vec3 {0.0f, 0.0f, 0.0f}, ngl::Vec3 {0.0f, 0.0f, 0.0f}, ngl::Vec3 {0.0f, 0.0f, 0.0f}, 1.0f, 1.0f, false); 

    ngl::Vec3 newPosition{4.0f, 10.0f, 0.0f};
    ngl::Vec3 newVelocity{0.0f, 0.6f, 0.0f};

    m.updateState(newPosition, newVelocity); // update the position and velocity

    EXPECT_EQ(m.getPosition(), newPosition);
    EXPECT_EQ(m.getVelocity(), newVelocity);
}

TEST(Mass, resetState)
{
    // Initial state of the mass m
    Mass m (ngl::Vec3 {4.0f, 5.0f, 0.0f}, ngl::Vec3 {0.0f, 0.0f, 0.0f}, ngl::Vec3 {5.0f, 7.0f, 0.0f}, ngl::Vec3 {1.0f, 3.0f, 0.0f}, 1.0f, 1.0f, false); 

    m.resetState(); // Reset the state

    ngl::Vec3 expectedPosition{0.0f, 0.0f, 0.0f};
    ngl::Vec3 expectedVelocity{0.0f, 0.0f, 0.0f};
    
    EXPECT_EQ(m.getPosition(), expectedPosition);
    EXPECT_EQ(m.getVelocity(), expectedVelocity);
}