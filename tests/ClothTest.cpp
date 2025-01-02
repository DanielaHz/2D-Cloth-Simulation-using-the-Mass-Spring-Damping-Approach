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

TEST (Cloth, createSpringConnectionsTestOneMass)
{ // I used ChatGPT to test this function!!
    Cloth c;
    int numMassWidth = 3;
    int numMassHeight = 3;

    c.createSpringConnections(numMassWidth, numMassHeight);

    std::pair<int, int> mass5 = {1, 1};
    std::vector<std::pair<int, int>> expectedNeighbors = {
        {0, 1}, {2, 1}, {1, 0}, {1, 2},
        {0, 0}, {0, 2}, {2, 0}, {2, 2}
    };

    // Search for the mass conecctions
    ASSERT_TRUE(c.connections.find(mass5) != c.connections.end()) << "mass not found!";
    const auto& neighbors = c.connections[mass5];

    // Find if all the connections are there
    for (const auto& neighbor : expectedNeighbors) {
        ASSERT_TRUE(std::find(neighbors.begin(), neighbors.end(), neighbor) != neighbors.end())
            << "Missing neighbor: (" << neighbor.first << ", " << neighbor.second << ")";
    }
}

TEST (Cloth, createSpringConnectionsTestAllMass)
{
    // I used ChatGPT to test this function!!
    Cloth c;
    int numMassWidth = 3;
    int numMassHeight = 3;

    c.createSpringConnections(numMassWidth, numMassHeight);

    // Iterate through all masses in the 3x3 grid
    for (int i = 0; i < numMassHeight; ++i) {
        for (int j = 0; j < numMassWidth; ++j) {
            std::pair<int, int> mass = {i, j};
            
            // Create a vector of expected neighbors for each mass
            std::vector<std::pair<int, int>> expectedNeighbors;
            
            // Add neighbors based on the position in the grid
            if (i > 0) expectedNeighbors.push_back({i - 1, j}); // Neighbor above
            if (i < numMassHeight - 1) expectedNeighbors.push_back({i + 1, j}); // Neighbor below
            if (j > 0) expectedNeighbors.push_back({i, j - 1}); // Neighbor to the left
            if (j < numMassWidth - 1) expectedNeighbors.push_back({i, j + 1}); // Neighbor to the right
            if (i > 0 && j > 0) expectedNeighbors.push_back({i - 1, j - 1}); // Top-left diagonal
            if (i > 0 && j < numMassWidth - 1) expectedNeighbors.push_back({i - 1, j + 1}); // Top-right diagonal
            if (i < numMassHeight - 1 && j > 0) expectedNeighbors.push_back({i + 1, j - 1}); // Bottom-left diagonal
            if (i < numMassHeight - 1 && j < numMassWidth - 1) expectedNeighbors.push_back({i + 1, j + 1}); // Bottom-right diagonal

            // Search for the mass connections
            ASSERT_TRUE(c.connections.find(mass) != c.connections.end()) << "Mass not found: (" << mass.first << ", " << mass.second << ")";

            const auto& neighbors = c.connections[mass];

            // Find if all the connections are there
            for (const auto& neighbor : expectedNeighbors) {
                ASSERT_TRUE(std::find(neighbors.begin(), neighbors.end(), neighbor) != neighbors.end())
                    << "Missing neighbor: (" << neighbor.first << ", " << neighbor.second << ") for mass (" << mass.first << ", " << mass.second << ")";
            }
        }
    }
}

TEST (Cloth, printConnectionsMap)
{

}


// TEST(Cloth, createSpring)
// {

// }