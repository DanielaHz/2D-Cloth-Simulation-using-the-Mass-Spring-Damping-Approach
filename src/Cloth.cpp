#include "Cloth.h"

void Cloth::initCloth(int width, int height, float spacing)
{
    std::cout << "Initializing cloth\n";

    int numMassWidth =  static_cast<int>(width/spacing);
    int numMassHeight = static_cast<int>(height/spacing);

    createMass(width, height, spacing);
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

void Cloth::createMass(int width, int height, float spacing)
{
    int numMassWidth = static_cast<int>(width/spacing);
    int numMassHeight = static_cast<int>(height/spacing);
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

void Cloth::createSpring(float spacing)

{   // recorre toda las unicas conexiones porque ese es el numero de resorte que dani va a crear
    for (auto e: uniqueConnections)
    {
        auto mass1Index = e.first;
        auto mass1VecConecctions = e.second;
        for (auto mass2Index : mass1VecConecctions)
        {
            // accedo a las masas que estan en el vector MassInSystem
            auto mass1 = std::make_shared<Mass>(massInSystem[mass1Index]);
            auto mass2 = std::make_shared<Mass>(massInSystem[mass2Index]);

            // calcula segun la posicion cuanto debria ser el spacing del resorte;
            float distance = (mass1->initPosition - mass2->initPosition).length();
            std::cout << "distance between particles is : " << distance << "\n";
            // creo spring
            Spring s(distance, mass1, mass2);
            springInSystem.push_back(s);
        }
    }
}

void Cloth::drawCloth()
{
    std::cout << "Executing the drawCloth here!!!" << "\n";

    drawMass();
    drawSpring();

    std::cout << "Finishing the drawCloth execution here!!!" << "\n";
}

void Cloth::drawMass()
{
    std::cout << "Drawing the mass in the system" << "\n";

    // transform the data of position in massInSystem to a GLfloat vector
    std::vector<GLfloat> vertexData;
    for (const auto& mass : massInSystem)
    {
        vertexData.push_back(mass.position.m_x);
        vertexData.push_back(mass.position.m_y);
        vertexData.push_back(mass.position.m_z);
    }

    for (size_t i = 0; i < vertexData.size(); i += 3)
    {
        std::cout << "Mass: " << i / 3 << ": (" << vertexData[i] << ", " << vertexData[i + 1] << ", " << vertexData[i + 2] << ")\n";
    }

    glPointSize(5.0f); 
    m_massVAO->bind();
    m_massVAO->setData(ngl::AbstractVAO::VertexData(vertexData.size() * sizeof(GLfloat), vertexData[0]));
    m_massVAO->setVertexAttributePointer(0, 3, GL_FLOAT, sizeof(GLfloat) * 3, 0);
    m_massVAO->setNumIndices(massInSystem.size());
    m_massVAO->draw();
    m_massVAO->unbind();
}

void Cloth::drawSpring()
{
    std::cout << "Drawing the springs in the system" << "\n";
    std::vector<GLfloat> vertexData;
    for (const auto& Spring : springInSystem)
    {
        vertexData.push_back(Spring.mass1->position.m_x);
        vertexData.push_back(Spring.mass1->position.m_y);
        vertexData.push_back(Spring.mass1->initPosition.m_z);

        vertexData.push_back(Spring.mass2->position.m_x);
        vertexData.push_back(Spring.mass2->position.m_y);
        vertexData.push_back(Spring.mass2->position.m_z);
    }

    for (size_t i = 0; i < vertexData.size(); i += 6)
    {
        std::cout << "Spring: " << i / 6 << ": Start(" << vertexData[i] << ", " << vertexData[i + 1] << ", " << vertexData[i + 2] << ") "
                  << "End(" << vertexData[i + 3] << ", " << vertexData[i + 4] << ", " << vertexData[i + 5] << ")\n";
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
    return -(deformation * stiffness * direction);
}

ngl::Vec3 Cloth::calcFinalForce(ngl::Vec3 gravity, ngl::Vec3 drag, ngl::Vec3 spring)
{
    return gravity + drag + spring;
}

void Cloth::evaluateForces()
{
    std::map<int, ngl::Vec3> trackSpringForces; // contain the index of the mass and the final force value acting over the mass

    for (size_t i = 0 ; i < massInSystem.size(); i++)
    {
        // calculate gravity
        std::cout << "-----" << "calculating the gravity force for the mass " << i << "-----" <<"\n";
        float mass = massInSystem[i].mass;
        std::cout << "mass : " << i << " have a mass value of: "<<  mass << "\n";
        ngl::Vec3 massGravity = calcGravityForce( gravity, mass);
        std::cout << "gravity force of the mass : " << i << " is : " << "(" << massGravity.m_x << "," << massGravity.m_y << "," << massGravity.m_z << ")" << "\n"; 

        // calculate drag
        std::cout << "-----" <<"calculating the drag force for the mass " << i << "-----" <<"\n";
        ngl::Vec3 velocity = massInSystem[i].velocity;
        std::cout << "mass : " << i << " have a velocity value of: (" << velocity.m_x << "," << velocity.m_y << "," <<  velocity.m_z << ")\n";
        ngl::Vec3 massDrag = calcDragForce(velocity, drag);
        std::cout << "drag force of the mass : " << i << " is : " << "(" << massDrag.m_x << "," << massDrag.m_y << "," << massDrag.m_z << ")" << "\n"; 


        // calculate springs force 
        std::cout << "-----" <<"calculating the spring forces for the mass " << i << "-----" <<"\n";
        // first I need to go inside uniqueconnections to identify how many spring are connected to i 
        int springsOveri =  uniqueConnections[i].size();
        std::cout << "the number of springs acting over the mass or connected to : " << i << " are : " << springsOveri << "\n";

       // second i go to the the springInSystem vector and i find the distance value and calculate for force 
        for (int l = 0 ; l < springsOveri; l++)
        {
            Spring s1 = springInSystem[l];
            ngl::Vec3 distance = s1.getMassPosition(s1.mass2) - s1.getMassPosition(s1.mass1); 
            float currentLength = s1.calculateCurrentLength(s1.mass1, s1.mass2);
            std::cout << "current length of the spring : " << currentLength << "\n";
            float deformation = currentLength - s1.restLength;
            std::cout << "deformation of the spring : " << deformation << "\n";
            ngl::Vec3 direction = distance / currentLength;
            ngl::Vec3 massSpring = calcSpringForce(deformation , s1.stiffness, direction);
            std::cout << "spring force of the mass : " << i << "is: ("<< massSpring.m_x << "," << massSpring.m_y << ","<< massSpring.m_z << ")\n";
            
            int indexMass1 = i;
            int indexMass2 = uniqueConnections[i][l];

            std::cout << "index mass " << indexMass1 << "\n";
            std::cout << "index mass " << indexMass2 << "\n";

            // guardo para i el valor de la fuerza como + y para las particulas conectadas a i la fuerza pero con -
            trackSpringForces[indexMass1] += massSpring;
            trackSpringForces[indexMass2] -= massSpring;
        }

        ngl::Vec3 finalMassSpring = trackSpringForces[i];

        ngl::Vec3 finalForce = calcFinalForce(massGravity, massDrag, finalMassSpring);

        finalForces[i] = finalForce;
    }

    for (auto e: finalForces)
    {
        std::cout << "the mass :" << e.first << " have a final force of: (" << e.second.m_x << "," << e.second.m_y << "," <<e.second.m_z << ")\n";
    }
}

void Cloth::requestNewState(float t, float dt)
{
    for (int i=0; i<massInSystem.size() ; i++)
    {
        Mass m1 = massInSystem[i];
        // create the states for any mass
        State intialState(m1.position, m1.velocity);

        // take the final force por mass
        ngl::Vec3 force = finalForces[i];
        std::cout<< "for the mass " << i << " final force is : " << force.m_x <<  force.m_y << force.m_z << "\n";

        // call the RK4 dani
        RK4Integrator RK4(intialState);
        RK4.integrate(t, dt, force);

        State updatedState = RK4.getState();

        ngl::Vec3 positionUpdateState =  updatedState.m_position;
        ngl::Vec3 velocityUpdateState =  updatedState.m_velocity;

        m1.updateState(positionUpdateState, velocityUpdateState);

        // print the new state
        std::cout << "update state position: (" << positionUpdateState.m_x << "," << positionUpdateState.m_y << "," <<positionUpdateState.m_z << ")\n";
        std::cout << "update state velocity: (" << velocityUpdateState.m_x <<  "," << velocityUpdateState.m_y << "," <<velocityUpdateState.m_z << ")\n";
    }
}