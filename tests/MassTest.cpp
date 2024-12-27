#include <gtest/gtest.h>
#include "Mass.h"

TEST(Mass, ctor)
{
    Mass m;
    EXPECT_FLOAT_EQ(m.mass, 1.0f);  
    EXPECT_FLOAT_EQ(m.size, 5.0f);
}
