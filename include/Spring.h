#ifndef SPRING_H_
#define SPRING_H_

class Spring {
public:
    float initLength = 0.0f;
    float finalLength = 0.0f;
    float stiffness = 0.0f;

    Spring() = default;
    Spring(float initLen, float finalLen, float stiffness);
    ~Spring() = default;
};
#endif
