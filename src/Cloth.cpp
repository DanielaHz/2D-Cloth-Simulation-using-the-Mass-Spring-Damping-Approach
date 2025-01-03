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
    // I took this function from CHATGPT -- please check the NCCA Reference! at the end of the project
    std::set<std::pair<int, int>> uniqueCon;  // set to track unique connections

    for (int i = 0; i < numMassHeight; ++i) 
    {
        for (int j = 0; j < numMassWidth; ++j) 
        {
            std::vector<int> neighbors; 
            int currentIndex = i * numMassWidth + j;

            std::vector<std::pair<int, int>> potentialNeighbors = {
                {i + 1, j},     // above
                {i - 1, j},     // below
                {i, j + 1},     // right
                {i, j - 1},     // left
                {i + 1, j + 1}, // Diagonal above-right
                {i + 1, j - 1}, // Diagonal above-left
                {i - 1, j + 1}, // Diagonal below-right
                {i - 1, j - 1}  // Diagonal below-left
            };

            for (const auto& neighbor : potentialNeighbors) 
            {
                int ni = neighbor.first;
                int nj = neighbor.second;

                // Validate if the potencial neighbor exist
                if (ni >= 0 && ni < numMassHeight && nj >= 0 && nj < numMassWidth) 
                {
                    int neighborIndex = ni * numMassWidth + nj; // calculate the index of the neighbor

                    // Make the connection using in the index
                    std::pair<int, int> connection = std::make_pair(currentIndex, neighborIndex);
                    std::pair<int, int> reverseConnection = std::make_pair(neighborIndex, currentIndex);

                    // add the conecction if it doesnt track it
                    if (uniqueCon.find(connection) == uniqueCon.end() && 
                        uniqueCon.find(reverseConnection) == uniqueCon.end()) 
                    {
                        uniqueCon.insert(connection);
                        neighbors.push_back(neighborIndex);
                    }
                }
            }
            uniqueConnections[currentIndex] = neighbors;
        }
    }
}

void Cloth::printConnectionsMap()
{
    for (auto e : uniqueConnections)
    {
        auto key = e.first; 
        auto value = e.second;

        std::cout << "The key value is: " << key << " ";
        std::cout << "The second value is: ";
        for (auto pair : value) {
            std::cout << pair << " "; }std::cout << "\n"; 
    }
}

void Cloth::createSpring()
{

}

