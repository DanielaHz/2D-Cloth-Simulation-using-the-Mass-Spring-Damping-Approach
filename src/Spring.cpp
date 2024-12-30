#include "Spring.h"

Spring::Spring(float initLen, float finalLen, float stiffness)
    : initLength{initLen}, finalLength{finalLen}, stiffness{stiffness} {}