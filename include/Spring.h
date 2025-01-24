#ifndef SPRING_H_
#define SPRING_H_
#include <memory>
#include "Mass.h"

class Spring {

    public:
        Spring() = default;
        Spring(float restLen, float currentLen, float stiffness, std::shared_ptr<Mass> m1, std::shared_ptr<Mass> m2);
        Spring(float restLen, float stiff, std::shared_ptr<Mass> m1, std::shared_ptr<Mass> m2);
        ~Spring() = default;
        ngl::Vec3 getMassPosition(std::shared_ptr<Mass> m);
        float calculateCurrentLength(std::shared_ptr<Mass> m1, std::shared_ptr<Mass> m2);
        float getRestLength();
        float getCurrentLength();
        float getStiffness();
        std::shared_ptr<Mass> getMass1();
        std::shared_ptr<Mass> getMass2();
        void setStiffness (const float &stiff);
        void setRestLength (const float &restLen);

    private:
        float m_restLength = 0.0f;
        float m_currentLength = 0.0f;
        float m_stiffness = 0.0f; 
        std::shared_ptr<Mass> m_mass1; // reference to mass1
        std::shared_ptr<Mass> m_mass2; // reference to mass2

};
#endif
