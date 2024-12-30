#ifndef SPRING_H_
#define SPRING_H_
#include <memory>
#include "Mass.h"

class Spring {
public:
    float initLength = 0.0f;
    float finalLength = 0.0f;
    float stiffness = 0.0f;
    // This pointer are to track the position of the mass an identify how much the spring has elongated.
    std::shared_ptr<Mass> mass1; //reference to mass1
    std::shared_ptr<Mass> mass2; // reference to mass2.

    Spring() = default;
    Spring(float initLen, float finalLen, float stiffness, std::shared_ptr<Mass> m1, std::shared_ptr<Mass> m2);
    ~Spring() = default;

    ngl::Vec3 getMassPosition(std::shared_ptr<Mass> m);
    float calculateFinalLength(std::shared_ptr<Mass> m1, std::shared_ptr<Mass> m2);

};
#endif
