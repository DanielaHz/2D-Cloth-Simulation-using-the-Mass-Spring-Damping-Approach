#include <gtest/gtest.h>
#include "Cloth.h"
#include <iostream>

// TEST(Cloth, InitCloth)
// {
//     std::vector<Mass> massInSystem;
//     std::vector<Spring>spingInSystem;

//     // receive this data as arguments
//     int width = 10;
//     int height = 10;
//     float spacing = 3;
//     int windowWidth = 1240;

//     //Create a cloth 
//     Cloth c;
//     // call placeMass
//     c.placeMass(width, height,spacing);

//     // call the placeSpring
//     c.placeSpring();

//     // pass the data to be render in the window
//     c.DrawCloth();

//     // The end is to display the grid of the mass in the window
// }

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
    float initY = 100.0f;
    float posZ = 0.0f;

    Cloth c;
    c.createMass(width, height, spacing);

    // check the first mass
    EXPECT_EQ(c.massInSystem[0].initPosition.m_x, initX);
    EXPECT_EQ(c.massInSystem[0].initPosition.m_y, initY);
    EXPECT_EQ(c.massInSystem[0].initPosition.m_z, posZ);
    EXPECT_TRUE(c.massInSystem[0].isFixed);
    GTEST_LOG_(INFO) << "Mass 1 position: " << c.massInSystem[0].initPosition.m_x << c.massInSystem[0].initPosition.m_y << c.massInSystem[0].initPosition.m_z << "\n";

    // check the 9 mass at the moment
    for (int i = 0; i < 9; ++i)
    {
        int row = i / numMassWidth;  
        int col = i % numMassWidth;  

        // Expected values
        float expectedX = initX + col * spacing;
        float expectedY = initY + row * spacing;

        EXPECT_EQ(c.massInSystem[i].initPosition.m_x, expectedX);
        EXPECT_EQ(c.massInSystem[i].initPosition.m_y, expectedY);
        EXPECT_EQ(c.massInSystem[i].initPosition.m_z, posZ);

        // show the positions
        GTEST_LOG_(INFO) << "Mass " << i + 1 << " position: "
                         << "x = " << c.massInSystem[i].initPosition.m_x << ", "
                         << "y = " << c.massInSystem[i].initPosition.m_y << ", "
                         << "z = " << c.massInSystem[i].initPosition.m_z << "\n";
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
    int numMassWidth = 10;
    int numMassHeight = 5;

    c.createSpringConnections(numMassWidth, numMassHeight);

    c.printConnectionsMap();
}


// TEST(Cloth, createSpring)
// {

// }