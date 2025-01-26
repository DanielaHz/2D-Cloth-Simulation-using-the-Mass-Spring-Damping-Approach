#include <gtest/gtest.h>
#include "Cloth.h"
#include <iostream>

TEST(Cloth, createMass)
{
    int numMassWidth = 3;
    int numMassHeight = 3;
    float spacing = 3.0f;
    int windowWidth = 1240;
    int width = numMassWidth*spacing;
    int totalMass = numMassWidth * numMassHeight;
    float initX = (windowWidth - width) / 2;
    float initY = 700.0f;
    float posZ = 0.0f;

    Cloth c;
    c.createMass(numMassWidth, numMassHeight, spacing);

    // check the first mass
    EXPECT_EQ(c.getMassInSystem()[0]->getInitPosition().m_x, initX);
    EXPECT_EQ(c.getMassInSystem()[0]->getInitPosition().m_y, initY);
    EXPECT_EQ(c.getMassInSystem()[0]->getInitPosition().m_z, posZ);
    EXPECT_TRUE(c.getMassInSystem()[0]->getIsFixed());
    GTEST_LOG_(INFO) << "Mass 1 position: " << c.getMassInSystem()[0]->getInitPosition().m_x << c.getMassInSystem()[0]->getInitPosition().m_y << c.getMassInSystem()[0]->getInitPosition().m_z << "\n";

    // check the 9 mass at the moment
    for (int i = 0; i < totalMass; ++i)
    {
        int row = i / numMassWidth;  
        int col = i % numMassWidth;  

        // Expected values
        float expectedX = initX + col * spacing;
        float expectedY = initY - row * spacing;

        EXPECT_EQ(c.getMassInSystem()[i]->getInitPosition().m_x, expectedX);
        EXPECT_EQ(c.getMassInSystem()[i]->getInitPosition().m_y, expectedY);
        EXPECT_EQ(c.getMassInSystem()[i]->getInitPosition().m_z, posZ);

        // show the positions
        GTEST_LOG_(INFO) << "Mass " << i + 1 << " position: "
                         << "x = " << c.getMassInSystem()[i]->getInitPosition().m_x << ", "
                         << "y = " << c.getMassInSystem()[i]->getInitPosition().m_y << ", "
                         << "z = " << c.getMassInSystem()[i]->getInitPosition().m_z << "\n";
    }
}

TEST(Cloth, createSpringConnectionsTestOneMass3X3Grid) { 
    Cloth c;
    int numMassWidth = 3;
    int numMassHeight = 3;
    c.setEnableStructuralSprings();
    c.createSpringConnections(numMassWidth, numMassHeight);

    int mass0 = 0;
    std::vector<int> expectedNeighbors = {3,1}; // Unique connections taking into count just the enable structural springs!!

    // Search for the mass connections
    ASSERT_TRUE(c.getUniqueConnections().find(mass0) != c.getUniqueConnections().end()) << "mass not found!";
    
    auto neighbors = c.getUniqueConnections().at(mass0);

    // Find if all the connections are there
    for (auto neighbor : expectedNeighbors) {
        ASSERT_TRUE(std::find(neighbors.begin(), neighbors.end(), neighbor) != neighbors.end()) << "Neighbor " << neighbor << " not found!";
    }
}

TEST (Cloth, printConnectionsMap)
{
    Cloth c;
    int numMassWidth = 3;
    int numMassHeight = 3;
    c.createSpringConnections(numMassWidth, numMassHeight);
    c.printConnectionsMap();
}

TEST(Cloth, createSpring)
{
    int numMassWidth = 3;
    int numMassHeight = 3;
    float spacing = 3.0f;
    int windowWidth = 1240;

    Cloth c;
    c.createMass(numMassWidth, numMassHeight, spacing);
    c.createSpringConnections (numMassWidth, numMassHeight);
    c.createSpring(spacing);

    int expectedSprings = 0;
    for (const auto& e : c.getUniqueConnections()) {
        expectedSprings += e.second.size();
    }
    ASSERT_EQ(c.getSpringInSystem().size(), expectedSprings);
}

TEST(Cloth, calcGravityForce)
{
    int numMassWidth = 3;
    int numMassHeight = 3;
    float spacing = 3.0f;
    ngl::Vec3 gravity = {0.0f, -9.8f, 0.0f};
    Cloth c;
    c.createMass(numMassWidth, numMassHeight, spacing);
    ngl::Vec3 gForce = c.calcGravityForce(gravity, c.getMassInSystem()[0]->getMass());
    float m1Mass = c.getMassInSystem()[0]->getMass();
    ngl::Vec3 gForceExpected = gravity * m1Mass;

    EXPECT_FLOAT_EQ(gForce.m_x, gForceExpected.m_x);
    EXPECT_FLOAT_EQ(gForce.m_y, gForceExpected.m_y);
    EXPECT_FLOAT_EQ(gForce.m_z, gForceExpected.m_z);
}

TEST (Cloth, calcDragForce)
{
    int numMassWidth = 3;
    int numMassHeight = 3;
    float spacing = 3.0f;
    Cloth c;
    float drag = 0.05f;
    
    c.createMass(numMassWidth, numMassHeight, spacing);
    ngl::Vec3 dForce = c.calcDragForce(c.getMassInSystem()[0]->getVelocity(), drag);

    ngl::Vec3 velocity =  c.getMassInSystem()[0]->getVelocity();
    ngl::Vec3 dForceExpected = -1 * (velocity * drag);

    EXPECT_FLOAT_EQ(dForce.m_x, dForceExpected.m_x);
    EXPECT_FLOAT_EQ(dForce.m_y, dForceExpected.m_y);
    EXPECT_FLOAT_EQ(dForce.m_z, dForceExpected.m_z);
}

TEST(Cloth, calcSpringForce)
{
    Cloth c;

    // Define test inputs
    float deformation = 1.0f;
    float stiffness = 10.0f;
    ngl::Vec3 direction(-1.0f, -2.0f, -3.0f);

    // Call the function to test
    ngl::Vec3 result = c.calcSpringForce(deformation, stiffness, direction);

    // Define expected output
    ngl::Vec3 expectedForce = ngl::Vec3(-10.0f, -20.0f, -30.0f);

    // Verify the results
    EXPECT_NEAR(result.m_x, expectedForce.m_x, 1e-5);
    EXPECT_NEAR(result.m_y, expectedForce.m_y, 1e-5);
    EXPECT_NEAR(result.m_z, expectedForce.m_z, 1e-5);
}

TEST(Cloth, calcSpringForce2)
{
    Cloth c;

    // Define test inputs
    float deformation = 1.0f;
    ngl::Vec3 direction (-4.0f, 2.0f, -1.5f);
    float stiffness = 5.0f;

    // Call the function to test
    ngl::Vec3 result = c.calcSpringForce(deformation, stiffness, direction);

    // Define expected output
    ngl::Vec3 expectedForce = ngl::Vec3(-20.0f, 10.0f, -7.5f);

    // Verify the results
    EXPECT_NEAR(result.m_x, expectedForce.m_x, 1e-5);
    EXPECT_NEAR(result.m_y, expectedForce.m_y, 1e-5);
    EXPECT_NEAR(result.m_z, expectedForce.m_z, 1e-5);
}

TEST(Cloth, evaluateForces)
{
    int numMassWidth = 3;
    int numMassHeight = 1;
    float spacing = 30.0f;
    int totalMass = numMassWidth * numMassHeight;

    float initX = 400;
    float initY = 650.0f;
    float posZ = 0.0f;

    Cloth c;
    c.createMass(numMassWidth, numMassHeight, spacing);
    c.createSpringConnections(numMassWidth, numMassHeight);
    c.createSpring(spacing);
    c.evaluateForces();

    for (int i = 0; i < totalMass; ++i)
    {
        ngl::Vec3 expectedGravity = c.calcGravityForce(c.getGravity(), 1.0f);
        ngl::Vec3 expectedDrag = c.calcDragForce(c.getMassInSystem()[i]->getVelocity(), c.getDrag());
        ngl::Vec3 expectedSpring = ngl::Vec3(0.0f, 0.0f, 0.0f); // Assuming initial spring forces are zero
        ngl::Vec3 expectedDamping = c.calcDampingForce(c.getMassInSystem()[i]->getVelocity(), 0.4f);
        ngl::Vec3 expectedForce = c.calcFinalForce(expectedGravity, expectedDrag, expectedSpring, expectedDamping);

        EXPECT_NEAR(c.getFinalForces()[i].m_x, expectedForce.m_x, 1e-4);
        EXPECT_NEAR(c.getFinalForces()[i].m_y, expectedForce.m_y, 1e-4);
        EXPECT_NEAR(c.getFinalForces()[i].m_z, expectedForce.m_z, 1e-4);
    }
}

TEST(Cloth, requestNewState)
{
    //This function pass the finalForces and the state to the RK4 and it returns the new state per any mass
    int numMassWidth = 3;
    int numMassHeight = 3;
    float spacing = 3.0f;
    Cloth c;
    c.createMass(numMassWidth, numMassHeight, spacing); // populate the massInSystem vector
    c.createSpringConnections(numMassWidth, numMassHeight); // create the map to contain the connections between mass
    c.createSpring(spacing); // populate the springInSystem vecotor
    c.evaluateForces(); // calculate the final force acting over any mass
    
    float t = 0.0f;  // should be accomulative and I shoul initialize this value in the simulation class
    float dt = 0.05; // this value is constant and it depends about the number of times Im going to update the simulation per second, exe: 20 times means 1/20 = 0.05;
    
    c.requestNewState( t ,dt);
}   