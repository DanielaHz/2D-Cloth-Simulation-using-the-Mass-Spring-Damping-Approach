#include "Cloth.h"

void Cloth::initCloth(int Width, int Height, float spacing)
{
    
}

void Cloth::placeMass(int width, int height, float spacing)
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