#include <gtest/gtest.h>
#include "Cloth.h"
#include <iostream>

TEST(Cloth, createMass)
{
    int width = 10;
    int height = 10;
    float spacing = 3;
    int windowWidth = 1240;

    int numMassWidth = static_cast<int>(width/spacing);
    int numMassHeight = static_cast<int>(height/spacing);
    int totalMass = numMassWidth * numMassHeight;

    float initX = (windowWidth - width) / 2;
    float initY = 650.0f;
    float posZ = 0.0f;

    Cloth c;
    c.createMass(numMassWidth, numMassHeight, spacing);

    // check the first mass
    EXPECT_EQ(c.massInSystem[0]->initPosition.m_x, initX);
    EXPECT_EQ(c.massInSystem[0]->initPosition.m_y, initY);
    EXPECT_EQ(c.massInSystem[0]->initPosition.m_z, posZ);
    EXPECT_TRUE(c.massInSystem[0]->isFixed);
    GTEST_LOG_(INFO) << "Mass 1 position: " << c.massInSystem[0]->initPosition.m_x << c.massInSystem[0]->initPosition.m_y << c.massInSystem[0]->initPosition.m_z << "\n";

    // check the 9 mass at the moment
    for (int i = 0; i < totalMass; ++i)
    {
        int row = i / numMassWidth;  
        int col = i % numMassWidth;  

        // Expected values
        float expectedX = initX + col * spacing;
        float expectedY = initY - row * spacing;

        EXPECT_EQ(c.massInSystem[i]->initPosition.m_x, expectedX);
        EXPECT_EQ(c.massInSystem[i]->initPosition.m_y, expectedY);
        EXPECT_EQ(c.massInSystem[i]->initPosition.m_z, posZ);

        // show the positions
        GTEST_LOG_(INFO) << "Mass " << i + 1 << " position: "
                         << "x = " << c.massInSystem[i]->initPosition.m_x << ", "
                         << "y = " << c.massInSystem[i]->initPosition.m_y << ", "
                         << "z = " << c.massInSystem[i]->initPosition.m_z << "\n";
    }
}

TEST (Cloth, createSpringConnectionsTestOneMass3X3Grid)
{ 
    Cloth c;
    int numMassWidth = 3;
    int numMassHeight = 3;

    c.createSpringConnections(numMassWidth, numMassHeight);

    int mass0 = 0;
    std::vector<int> expectedNeighbors = {1, 3, 4}; // Unique connections

    // Search for the mass conecctions
    ASSERT_TRUE(c.uniqueConnections.find(mass0) != c.uniqueConnections.end()) << "mass not found!";
    
    const auto& neighbors = c.uniqueConnections[mass0];

    // Find if all the connections are there
    for (const auto& neighbor : expectedNeighbors) {
        ASSERT_TRUE(std::find(neighbors.begin(), neighbors.end(), neighbor) != neighbors.end());}
}

TEST (Cloth, printConnectionsMap)
{
    Cloth c;
    int numMassWidth = 3;
    int numMassHeight = 3;

    c.createSpringConnections(numMassWidth, numMassHeight);

    c.printConnectionsMap();
    std::cout << "print all the connections map: " << "\n";
    c.printAllConnections();
}

TEST(Cloth, createSpring)
{
    int width = 10;
    int height = 10;
    float spacing = 3.0f;
    int windowWidth = 1240;

    int numMassWidth = static_cast<int>(width/spacing);
    int numMassHeight = static_cast<int>(height/spacing);
    int totalMass = numMassWidth * numMassHeight;

    float initX = (windowWidth - width) / 2;
    float initY = 100.0f;
    float posZ = 0.0f;

    Cloth c;
    c.createMass(width, height, spacing);
    c.createSpringConnections (numMassWidth, numMassHeight);
    c.createSpring(spacing);

    int expectedSprings = 0;
    for (const auto& e : c.uniqueConnections) {
        expectedSprings += e.second.size();
    }
    ASSERT_EQ(c.springInSystem.size(), expectedSprings);
}

TEST(Cloth, calcGravityForce)
{
    int width = 10;
    int height = 10;
    float spacing = 3;
    Cloth c;
    ngl::Vec3 gravity = {0.0f, -9.8f, 0.0f};
    c.createMass(width, height, spacing);
    ngl::Vec3 gForce = c.calcGravityForce(gravity, c.massInSystem[0]->mass);
    float m1Mass = c.massInSystem[0]->mass;
    ngl::Vec3 gForceExpected = gravity * m1Mass;

    EXPECT_FLOAT_EQ(gForce.m_x, gForceExpected.m_x);
    EXPECT_FLOAT_EQ(gForce.m_y, gForceExpected.m_y);
    EXPECT_FLOAT_EQ(gForce.m_z, gForceExpected.m_z);
}

TEST (Cloth, calcDragForce)
{
    int width = 10;
    int height = 10;
    float spacing = 3;
    Cloth c;
    float drag = 0.05f;
    c.createMass(width, height, spacing);
    ngl::Vec3 dForce = c.calcDragForce(c.massInSystem[0]->velocity, drag);

    ngl::Vec3 velocity =  c.massInSystem[0]->velocity;
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

    // Verify the results
    for (int i = 0; i < totalMass; ++i)
    {
        ngl::Vec3 expectedGravity = c.calcGravityForce(c.gravity, 1.0f);
        ngl::Vec3 expectedDrag = c.calcDragForce(c.massInSystem[i]->velocity, c.drag);
        ngl::Vec3 expectedSpring = ngl::Vec3(0.0f, 0.0f, 0.0f); // Assuming initial spring forces are zero
        ngl::Vec3 expectedDamping = c.calcDampingForce(c.massInSystem[i]->velocity, 0.4f);
        ngl::Vec3 expectedForce = c.calcFinalForce(expectedGravity, expectedDrag, expectedSpring, expectedDamping);

        EXPECT_NEAR(c.finalForces[i].m_x, expectedForce.m_x, 1e-4);
        EXPECT_NEAR(c.finalForces[i].m_y, expectedForce.m_y, 1e-4);
        EXPECT_NEAR(c.finalForces[i].m_z, expectedForce.m_z, 1e-4);
    }
}

TEST(Cloth, requestNewState)
{
    //This function pass the finalForces and the state to the RK4 and it returns the new state per any mass
    int width = 10;
    int height = 10;
    float spacing = 3.0f;
    int windowWidth = 1240;

    int numMassWidth = static_cast<int>(width / spacing);
    int numMassHeight = static_cast<int>(height / spacing);
    int totalMass = numMassWidth * numMassHeight;

    float initX = (windowWidth - width) / 2;
    float initY = 100.0f;
    float posZ = 0.0f;

    Cloth c;
    c.createMass(numMassWidth, numMassHeight, spacing); // populate the massInSystem vector
    c.createSpringConnections(numMassWidth, numMassHeight); // create the map to contain the connections between mass
    c.createSpring(spacing); // populate the springInSystem vecotor
    c.evaluateForces(); // calculate the final force acting over any mass
    
    float t = 0.0f;  // should be accomulative and I shoul initialize this value in the simulation class
    float dt = 0.05; // this value is constant and it depends about the number of times Im going to update the simulation per second, exe: 20 times means 1/20 = 0.05;
    
    c.requestNewState( t ,dt);
}   