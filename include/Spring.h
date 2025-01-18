#ifndef SPRING_H_
#define SPRING_H_
#include <memory>
#include "Mass.h"

class Spring {
public:
    float restLength = 0.0f;
    float currentLength = 0.0f;
    float stiffness = 1.0f; 
    std::shared_ptr<Mass> mass1; // reference to mass1
    std::shared_ptr<Mass> mass2; // reference to mass2

    Spring() = default;
    Spring(float restLen, float currentLen, float stiffness, std::shared_ptr<Mass> m1, std::shared_ptr<Mass> m2);
    Spring(float restLen, float stiff, std::shared_ptr<Mass> m1, std::shared_ptr<Mass> m2);
    ~Spring() = default;

    ngl::Vec3 getMassPosition(std::shared_ptr<Mass> m);
    float calculateCurrentLength(std::shared_ptr<Mass> m1, std::shared_ptr<Mass> m2);
};
#endif
