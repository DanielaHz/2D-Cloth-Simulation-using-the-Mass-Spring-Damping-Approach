#include "Cloth.h"

void Cloth::initCloth(int numMassWidth, int numMassHeight, float spacing)
{
    std::cout << "Initializing cloth\n";

    createMass(numMassWidth, numMassHeight, spacing);
    createSpringConnections(numMassWidth, numMassHeight);
    createSpring(spacing);

    if (massInSystem.empty())
    {
        std::cerr << "Error: massInSystem is empty after to createMass\n";
        return;
    }

    if (springInSystem.empty())
    {
        std::cerr << "Error: springInSystem is empty after to createSpring\n";
        return;
    }

    // Initializing the VAO for mass
    m_massVAO = ngl::VAOFactory::createVAO(ngl::simpleVAO, GL_POINTS);
    m_massVAO->bind();
    m_massVAO->setNumIndices(massInSystem.size());
    m_massVAO->unbind();

    // Initializing the VAO for springs
    m_springVAO = ngl::VAOFactory::createVAO(ngl::simpleVAO, GL_LINES);
    m_springVAO->bind();
    m_springVAO->setNumIndices(springInSystem.size());
    m_springVAO->unbind();

    std::cout << "VAOs initializing correctly :)\n";
}

void Cloth::createMass(int numMassWidth, int numMassHeight, float spacing)
{   
    int width = numMassWidth*spacing;
    int totalMass = numMassWidth * numMassHeight;
    float initX = (windowWidth - width)/2;
    float initY = 650.0f;
    float initZ = 0.0f;

    for (int i = 0; i < totalMass; i++)
    {
        int row = i / numMassWidth;  
        int col = i % numMassWidth; 

        float x = initX + col * spacing;  
        float y = initY - row * spacing;  
        float z = initZ;            

        // Creating the ngl::Vec3 position  
        ngl::Vec3 initPos = {x, y, z};

        bool isFixed = (row == 0) && (col == 0 || col == numMassWidth - 1); // this is for fixded the first one and the last one in the grid
        // bool isFixed = (row == 0) && (col == 0); //this is for fixed the firs one 

        // creating the mass
        Mass m1(initPos, isFixed);
        // massInSystem.push_back(m1);
        massInSystem.push_back(std::make_shared<Mass>(m1));

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

                    allConnections[currentIndex].push_back(neighborIndex);

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

void Cloth::printAllConnections()
{
    for (auto e : allConnections)
    {
        auto key = e.first; 
        auto value = e.second;

        std::cout << "The key value is: " << key << " ";
        std::cout << "The second value is: ";
        for (auto pair : value) {
            std::cout << pair << " "; }std::cout << "\n"; 
    }
}

void Cloth::createSpring(float spacing) {
    for (auto e : uniqueConnections) {
        auto mass1Index = e.first;
        auto mass1VecConnections = e.second;
        for (auto mass2Index : mass1VecConnections) {
            auto mass1 = massInSystem[mass1Index];
            auto mass2 = massInSystem[mass2Index];

            float distance = (mass1->initPosition - mass2->initPosition).length();

            float stiffness1 = 5.0f;
            float stiffness2 = 1.2f;
            float stiffness3 = 2.5f;

            // this if to create springs with different stiffness values 
            if (distance > spacing)
            {
                Spring s(distance, stiffness2, mass1, mass2);
                springInSystem.push_back(s);
            }
            else if ( distance == spacing)
            {
                Spring s(distance, stiffness1, mass1, mass2);
                springInSystem.push_back(s);   
            }
            else 
            {
                Spring s(distance, stiffness3, mass1, mass2);
                springInSystem.push_back(s);
            }
        }
    }
}

void Cloth::drawCloth()
{
    drawMass();
    drawSpring();
}

void Cloth::drawMass()
{
    // transform the data of position in massInSystem to a GLfloat vector
    std::vector<GLfloat> vertexData;
    for (const auto& mass : massInSystem)
    {
        vertexData.push_back(mass->position.m_x);
        vertexData.push_back(mass->position.m_y);
        vertexData.push_back(mass->position.m_z);
    }

    glPointSize(7.0f); 
    m_massVAO->bind();
    m_massVAO->setData(ngl::AbstractVAO::VertexData(vertexData.size() * sizeof(GLfloat), vertexData[0]));
    m_massVAO->setVertexAttributePointer(0, 3, GL_FLOAT, sizeof(GLfloat) * 3, 0);
    m_massVAO->setNumIndices(massInSystem.size());
    m_massVAO->draw();
    m_massVAO->unbind();
}

void Cloth::drawSpring()
{
    std::vector<GLfloat> vertexData;
    for (const auto& Spring : springInSystem)
    {
        vertexData.push_back(Spring.mass1->position.m_x);
        vertexData.push_back(Spring.mass1->position.m_y);
        vertexData.push_back(Spring.mass1->position.m_z);

        vertexData.push_back(Spring.mass2->position.m_x);
        vertexData.push_back(Spring.mass2->position.m_y);
        vertexData.push_back(Spring.mass2->position.m_z);
    }

    m_springVAO->bind();
    m_springVAO->setData(ngl::AbstractVAO::VertexData(vertexData.size() * sizeof(GLfloat), vertexData[0]));
    m_springVAO->setVertexAttributePointer(0, 3, GL_FLOAT, sizeof(GLfloat) * 3, 0);
    m_springVAO->setNumIndices(springInSystem.size() * 2);
    m_springVAO->draw();
    m_springVAO->unbind();
}

ngl::Vec3 Cloth::calcGravityForce(ngl::Vec3 gravity, float mass)
{
    return mass * gravity;
}

ngl::Vec3 Cloth::calcDragForce(ngl::Vec3 velocity, float drag)
{
    return -velocity * drag;
}

ngl::Vec3 Cloth::calcSpringForce(float deformation, float stiffness, ngl::Vec3 direction)
{
    return (deformation * stiffness * direction);
}

ngl::Vec3 Cloth::calcDampingForce(ngl::Vec3 velocity, float damping)
{
    return -(velocity * damping);
}

ngl::Vec3 Cloth::calcFinalForce(ngl::Vec3 gravity, ngl::Vec3 drag, ngl::Vec3 spring, ngl::Vec3 damping)
{
    return gravity + drag + spring + damping;
}

void Cloth::evaluateForces()
{
    std::map<int, ngl::Vec3> trackSpringForces;

    for (size_t i = 0 ; i < massInSystem.size(); i++)
    {
        // Calculate the gravity force
        float mass = massInSystem[i]->mass;
        ngl::Vec3 massGravity = calcGravityForce(gravity, mass);

        // Calculate the drag force
        ngl::Vec3 velocity = massInSystem[i]->velocity;
        ngl::Vec3 massDrag = calcDragForce(velocity, drag);

        // Calculate the spring force 
        int springsOveri = uniqueConnections[i].size();
        for (int l = 0 ; l < springsOveri; l++)
        {
            int indexMass2 = uniqueConnections[i][l];
            Spring s1 = springInSystem[l];
            ngl::Vec3 direction = massInSystem[indexMass2]->position - massInSystem[i]->position;
            float distance = direction.length();
            float deformation =  distance - s1.restLength;
            direction.normalize();
            ngl::Vec3 force = calcSpringForce(deformation, s1.stiffness , direction);

            // Adding the force accting over the mass i 
            trackSpringForces[i] += force;
            trackSpringForces[indexMass2] -= force;
        }

        ngl::Vec3 massSpring = trackSpringForces[i];

        // Calculating damping force 
        float damping = 0.4f;
        ngl::Vec3 massDamping = calcDampingForce(velocity, damping);

        // Calculate the final force in the system
        ngl::Vec3 finalForce = calcFinalForce(massGravity, massDrag, massSpring, massDamping);

        // Final force acting over the mass
        finalForces[i] = finalForce;
    }
}

void Cloth::requestNewState(float t, float dt)
{

    for (int i=0; i<massInSystem.size() ; i++)
    {
        Mass& m1 = *massInSystem[i];

        // create the states for any mass
        State intialState(m1.position, m1.velocity);

        // take the final force por mass
        ngl::Vec3 force = finalForces[i];

        // call the RK4 
        RK4Integrator RK4(intialState);
        RK4.integrate(t, dt, force);

        State updatedState = RK4.getState();

        ngl::Vec3 positionUpdateState =  updatedState.m_position;
        ngl::Vec3 velocityUpdateState =  updatedState.m_velocity;

        if (m1.isFixed == false)
        {
            m1.position = positionUpdateState;
            m1.velocity = velocityUpdateState;
        }
    }
}