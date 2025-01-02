#include "Cloth.h"

void Cloth::initCloth(int width, int height, float spacing)
{
    
}

void Cloth::createMass(int width, int height, float spacing)
{
    int numMassWidth = static_cast<int>(width/spacing);
    int numMassHeight = static_cast<int>(height/spacing);
    int totalMass = numMassWidth * numMassHeight;

    float initX = (windowWidth - width)/2;
    float initY = 100.0f;
    float initZ = 0.0f;

    for (int i = 0; i < totalMass; i++)
    {
        int row = i / numMassWidth;  
        int col = i % numMassWidth; 

        float x = initX + col * spacing;  
        float y = initY + row * spacing;  
        float z = initZ;            

        // Creating the ngl::Vec3 position  
        ngl::Vec3 initPos = {x, y, z};

        bool isFixed = (row == 0) && (col == 0 || col == numMassWidth - 1);

        // creating the mass
        Mass m1(initPos, isFixed);

        massInSystem.push_back(m1);
    }
}

void Cloth::createSpringConnections(int numMassWidth, int numMassHeight)
{
    for (int i = 0; i < numMassHeight; ++i) 
    {
        for (int j = 0; j < numMassWidth; ++j) 
        {
            std::vector<std::pair<int, int>> neighbors;

            if (i + 1 < numMassHeight) {neighbors.emplace_back(i + 1, j);} // Neighbor below
            if (i - 1 >= 0) {neighbors.emplace_back(i - 1, j);} // Neighbor above
            if (j + 1 < numMassWidth) {neighbors.emplace_back(i, j + 1);} // Neighbor right
            if (j - 1 >= 0) {neighbors.emplace_back(i, j - 1);} // Neighbor left
            if (i + 1 < numMassHeight && j + 1 < numMassWidth) {neighbors.emplace_back(i + 1, j + 1);} // Neighbor diagonally below-right
            if (i + 1 < numMassHeight && j - 1 >= 0) {neighbors.emplace_back(i + 1, j - 1);} // Neighbor diagonally below-left
            if (i - 1 >= 0 && j + 1 < numMassWidth) {neighbors.emplace_back(i - 1, j + 1);} //  Neighbor diagonally above-righ
            if (i - 1 >= 0 && j - 1 >= 0) {neighbors.emplace_back(i - 1, j - 1);} //  Neighbor diagonally above-left

            // Asignar la lista de vecinos al mapa
            connections[{i, j}] = neighbors;
        }
    }
}

void Cloth::createSpring()
{

}

