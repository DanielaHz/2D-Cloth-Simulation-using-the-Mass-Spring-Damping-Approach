#include "Cloth.h"

void Cloth::initCloth(int numMassWidth, int numMassHeight, float spacing)
{
    std::cout << "Initializing cloth\n";

    createMass(numMassWidth, numMassHeight, spacing);
    createSpringConnections(numMassWidth, numMassHeight);
    createSpring(spacing);

    if (m_massInSystem.empty())
    {
        std::cerr << "Error: massInSystem is empty after to createMass\n";
        return;
    }

    if (m_springInSystem.empty())
    {
        std::cerr << "Error: springInSystem is empty after to createSpring\n";
        return;
    }

    // Initializing the VAO for masses
    m_massVAO = ngl::VAOFactory::createVAO(ngl::simpleVAO, GL_POINTS);
    m_massVAO->bind();
    m_massVAO->setNumIndices(m_massInSystem.size());
    m_massVAO->unbind();

    // Initializing the VAO for springs
    m_springVAO = ngl::VAOFactory::createVAO(ngl::simpleVAO, GL_LINES);
    m_springVAO->bind();
    m_springVAO->setNumIndices(m_springInSystem.size());
    m_springVAO->unbind();

    std::cout << "VAOs initializing correctly :)\n";
}

void Cloth::createMass(int numMassWidth, int numMassHeight, float spacing)
{   
    int width = numMassWidth*spacing;
    int totalMass = numMassWidth * numMassHeight;
    float initX = (m_windowWidth - width)/2;
    float initY = 700.0f;
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

        // This is for fixded the first one and the last one in the grid
        bool isFixed = (row == 0) && (col == 0 || col == numMassWidth - 1 || col == numMassWidth/2);
 
        // creating the mass
        Mass m1(initPos, isFixed);

        m_massInSystem.push_back(std::make_shared<Mass>(m1));
    }
}

void Cloth::createSpringConnections(int numMassWidth, int numMassHeight)
{
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
                // {i + 1, j + 1}, // Diagonal above-right
                // {i + 1, j - 1}, // Diagonal above-left
                // {i - 1, j + 1}, // Diagonal below-right
                // {i - 1, j - 1} // Diagonal below-left
                // {i + 2, j},     // above
                // {i - 2, j},     // below
                // {i, j + 2},     // right
                // {i, j - 2},     // left
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

                    m_allConnections[currentIndex].push_back(neighborIndex);

                    // add the conecction if it doesnt track it
                    if (uniqueCon.find(connection) == uniqueCon.end() && 
                        uniqueCon.find(reverseConnection) == uniqueCon.end()) 
                    {
                        uniqueCon.insert(connection);
                        neighbors.push_back(neighborIndex);
                    }
                }
            }
            m_uniqueConnections[currentIndex] = neighbors;
        }
    }
    printTotalSpings();
}

void Cloth::printConnectionsMap()
{
    for (auto e : m_uniqueConnections)
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
    for (auto e : m_allConnections)
    {
        auto key = e.first; 
        auto value = e.second;

        std::cout << "The key value is: " << key << " ";
        std::cout << "The second value is: ";
        for (auto pair : value) {
            std::cout << pair << " "; }std::cout << "\n"; 
    }
}

int Cloth::printTotalSpings()
{
    int totalSprings = 0;
    for (auto e: m_uniqueConnections)
    {
        int springsbymass = e.second.size();
        totalSprings += springsbymass;
    }
    std::cout << "the total of springs created are: "<< totalSprings << "\n";
    return totalSprings;
}

void Cloth::createSpring(float spacing) 
{
    // Go over the uniqueConnections map and create the springs with the respective 
    for (auto e : m_uniqueConnections) 
    {
        auto mass1Index = e.first;
        auto mass1VecConnections = e.second;

        for (auto mass2Index : mass1VecConnections) 
        {
            auto mass1 = m_massInSystem[mass1Index];
            auto mass2 = m_massInSystem[mass2Index];

            float distance = (mass1->getInitPosition() - mass2->getInitPosition()).length();

            if (distance == spacing) {
                Spring s(distance, m_structuralStiffness, mass1, mass2); // Structural springs have the same length that the spacing between masses
                m_springInSystem.push_back(s);   
            } else if (distance > spacing && distance < spacing * 2) { 
                Spring s(distance, m_shearStiffness, mass1, mass2);      // Shear springs represents diagonal conenctions which are a little bit bigger that the strucutral applyin pitagoras theorem
                m_springInSystem.push_back(s);
            } else if (distance == spacing *2 ) {
                Spring s(distance, m_bendStiffness, mass1, mass2);      // bend springs are the doble lenght of the structural
                m_springInSystem.push_back(s);
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
    for (const auto& mass : m_massInSystem)
    {
        vertexData.push_back(mass->getPosition().m_x);
        vertexData.push_back(mass->getPosition().m_y);
        vertexData.push_back(mass->getPosition().m_z);
    }

    glPointSize(m_massInSystem[0]->getSize()); // set the size of the point mass
    m_massVAO->bind();
    m_massVAO->setData(ngl::AbstractVAO::VertexData(vertexData.size() * sizeof(GLfloat), vertexData[0]));
    m_massVAO->setVertexAttributePointer(0, 3, GL_FLOAT, sizeof(GLfloat) * 3, 0);
    m_massVAO->setNumIndices(m_massInSystem.size());
    m_massVAO->draw();
    m_massVAO->unbind();
}

void Cloth::drawSpring()
{
    // transform the data of position in springsInSystem to a GLfloat vector
    std::vector<GLfloat> vertexData;
    for (auto &Spring : m_springInSystem)
    {
        vertexData.push_back(Spring.getMass1()->getPosition().m_x);
        vertexData.push_back(Spring.getMass1()->getPosition().m_y);
        vertexData.push_back(Spring.getMass1()->getPosition().m_z);

        vertexData.push_back(Spring.getMass2()->getPosition().m_x);
        vertexData.push_back(Spring.getMass2()->getPosition().m_y);
        vertexData.push_back(Spring.getMass2()->getPosition().m_z);
    }

    m_springVAO->bind();
    m_springVAO->setData(ngl::AbstractVAO::VertexData(vertexData.size() * sizeof(GLfloat), vertexData[0]));
    m_springVAO->setVertexAttributePointer(0, 3, GL_FLOAT, sizeof(GLfloat) * 3, 0);
    m_springVAO->setNumIndices(m_springInSystem.size() * 2);
    m_springVAO->draw();
    m_springVAO->unbind();
}

ngl::Vec3 Cloth::calcGravityForce(ngl::Vec3 m_gravity, float mass) {
    return mass * m_gravity;
}

ngl::Vec3 Cloth::calcDragForce(ngl::Vec3 velocity, float m_drag)
{
    return -velocity * m_drag;
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
    std::map<int, ngl::Vec3> trackSpringForces; // provitional map

    for (size_t i = 0 ; i < m_massInSystem.size(); i++)
    {
        // Calculate the gravity force
        float mass = m_massInSystem[i]->getMass();
        ngl::Vec3 massGravity = calcGravityForce(m_gravity, mass);

        // Calculate the drag force
        ngl::Vec3 velocity = m_massInSystem[i]->getVelocity();
        ngl::Vec3 massDrag = calcDragForce(velocity, m_drag);

        // Calculate the spring forces
        int springsOveri = m_uniqueConnections[i].size();
        for (int l = 0 ; l < springsOveri; l++)
        {
            int indexMass2 = m_uniqueConnections[i][l];
            Spring s1 = m_springInSystem[l];
            ngl::Vec3 direction = m_massInSystem[indexMass2]->getPosition() - m_massInSystem[i]->getPosition();
            float distance = direction.length();
            float deformation =  distance - s1.getRestLength();
            direction.normalize();
            ngl::Vec3 force = calcSpringForce(deformation, s1.getStiffness(), direction);

            // Adding the force accting over the mass i and the other connected in the spring
            trackSpringForces[i] += force;
            trackSpringForces[indexMass2] -= force;  
        }

        ngl::Vec3 massSpring = trackSpringForces[i]; // the the total value of the spring forces over the mass i

        // Calculate the damping force
        ngl::Vec3 massDamping = calcDampingForce(velocity, m_damping);

        // Calculate the final force over the mass i
        ngl::Vec3 finalForce = calcFinalForce(massGravity, massDrag, massSpring, massDamping);

        // Final force acting over the mass i
        m_finalForces[i] = finalForce;
    }
}

void Cloth::requestNewState(float t, float dt)
{
    for (int i=0; i<m_massInSystem.size() ; i++)
    {
        Mass& m1 = *m_massInSystem[i];

        // create the states for any mass
        State intialState(m1.getPosition(), m1.getVelocity());

        // take the final force por mass
        ngl::Vec3 force = m_finalForces[i];

        // call the RK4 
        RK4Integrator RK4(intialState);
        RK4.integrate(t, dt, force);

        State updatedState = RK4.getState();

        ngl::Vec3 positionUpdateState =  updatedState.m_position;
        ngl::Vec3 velocityUpdateState =  updatedState.m_velocity;

        if (m1.getIsFixed() == false)
        {
            m1.setPosition(positionUpdateState);
            m1.setVelocity(velocityUpdateState);
        }
    }
}

std::vector<std::shared_ptr<Mass>> Cloth::getMassInSystem() {return m_massInSystem;}

std::vector<Spring> Cloth::getSpringInSystem() {return m_springInSystem;}

std::map<int, std::vector<int>> Cloth::getUniqueConnections() {return m_uniqueConnections;}

std::map<int, std::vector<int>> Cloth::getAllConnections() {return m_allConnections;}

std::map<int, ngl::Vec3> Cloth::getFinalForces() {return m_finalForces;}

float Cloth::getDrag() {return m_drag;}

ngl::Vec3 Cloth::getGravity() {return m_gravity;}

// void Cloth::applyLeftClickForce(const ngl::Vec2 &clickPosition, float forceRadius, float forceMagnitude)
// {
//     for (size_t i = 0; i < m_massInSystem.size(); ++i)
//     {
//         ngl::Vec2 massPosition = m_massInSystem[i]->getPosition();
//         float distance = (massPosition - clickPosition).length();

//         if (distance <= forceRadius)
//         {
//             ngl::Vec3 force(0.0f, 0.0f, forceMagnitude);
//             m_finalForces[i] += force;
//         }
//     }
// }
