#ifndef SPRING_H_
#define SPRING_H_
#include <memory>
#include "Mass.h"

// This class represents the methods and attributes that a spring has in the simulation.

class Spring {

    public:
        Spring() = default; // Default constructor

        // Parametrized constructors
        Spring(float restLen, float currentLen, float stiffness, std::shared_ptr<Mass> m1, std::shared_ptr<Mass> m2);
        Spring(float restLen, float stiff, std::shared_ptr<Mass> m1, std::shared_ptr<Mass> m2);

        ~Spring() = default; // Default destructor 

        // Getter methods
        float getRestLength();
        float getCurrentLength();
        float getStiffness();
        std::shared_ptr<Mass> getMass1();
        std::shared_ptr<Mass> getMass2();

        // Setter methods
        void setStiffness (const float &stiff);
        void setRestLength (const float &restLen);

        // Methods
        ngl::Vec3 getMassPosition(std::shared_ptr<Mass> m); // Return the position of the mass attached to the spring
        float calculateCurrentLength(std::shared_ptr<Mass> m1, std::shared_ptr<Mass> m2); // Calculate the distance between the two point masses, which defines the current length of the spring
        
    private:
        // Attributes
        float m_restLength = 0.0f;     // Rest length given by the spacing value in the cloth constructor
        float m_currentLength = 0.0f;  // Current length
        float m_stiffness = 0.0f;      // Stiffness constant
        std::shared_ptr<Mass> m_mass1; // Reference to mass1
        std::shared_ptr<Mass> m_mass2; // Reference to mass2

};
#endif
