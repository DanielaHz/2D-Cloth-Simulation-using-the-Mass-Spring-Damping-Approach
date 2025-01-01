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
    ngl::Vec3 initPos{1.0f, 2.0f, 0.0f}; // Remember is a 2D animation so z = 0.0f
    ngl::Vec3 initVel{0.1f, 0.2f, 0.0f};
    ngl::Vec3 pos{4.0f, 5.0f, 0.0f};
    ngl::Vec3 vel{0.4f, 0.5f, 0.0f};
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

    //////////////////////////////////////////////////////
    ngl::Vec3 initPosition = {5.0f, 0.0f, 0.0f};
    ngl::Vec3 initVelocity = {0.0f, 0.0f, 0.0f};
    ngl::Vec3 position = {0.0f, 0.0f, 0.0f};
    ngl::Vec3 velocity = {0.0f, 0.0f, 0.0f};
    float mass2 = 1.0f; 
    float size2 = 5.0f;

    Mass m2(ngl::Vec3 {5.0f, 0.0f, 0.0f}, isFixed = true);
    EXPECT_EQ(m2.initPosition, initPosition);
    EXPECT_EQ(m2.initVelocity, initVelocity);
    EXPECT_EQ(m2.position, position);
    EXPECT_EQ(m2.velocity, velocity);
    EXPECT_FLOAT_EQ(m2.mass, mass2);
    EXPECT_FLOAT_EQ(m2.size, size2);
    EXPECT_TRUE(m2.isFixed);
}

TEST(Mass, updateState)
{   
    // Initial state of the mass m
    Mass m (ngl::Vec3 {4.0f, 5.0f, 0.0f}, ngl::Vec3 {0.0f, 0.0f, 0.0f}, ngl::Vec3 {0.0f, 0.0f, 0.0f}, ngl::Vec3 {0.0f, 0.0f, 0.0f}, 1.0f, 1.0f, false); 

    // Values should calculate for the RK4 - default values for now.
    ngl::Vec3 newPosition{4.0f, 10.0f, 0.0f};
    ngl::Vec3 newVelocity{0.0f, 0.6f, 0.0f};

    m.updateState(newPosition, newVelocity); // update the position and velocity

    EXPECT_EQ(m.position, newPosition);
    EXPECT_EQ(m.velocity, newVelocity);
}

TEST(Mass, resetState)
{
    // Should reset position and velocity to {0.0f, 0.0f, 0.0f}
    Mass m (ngl::Vec3 {4.0f, 5.0f, 0.0f}, ngl::Vec3 {0.0f, 0.0f, 0.0f}, ngl::Vec3 {5.0f, 7.0f, 0.0f}, ngl::Vec3 {1.0f, 3.0f, 0.0f}, 1.0f, 1.0f, false); 

    m.resetState(); // Reset the state

    ngl::Vec3 expectedPosition{0.0f, 0.0f, 0.0f};
    ngl::Vec3 expectedVelocity{0.0f, 0.0f, 0.0f};
    
    EXPECT_EQ(m.position, expectedPosition);
    EXPECT_EQ(m.velocity, expectedVelocity);
}