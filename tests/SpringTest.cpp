#include <gtest/gtest.h>
#include "Spring.h"

TEST(Spring, DefaultConstructor)
{
    Spring s;
    EXPECT_FLOAT_EQ(s.initLength, 0.0f);
    EXPECT_FLOAT_EQ(s.finalLength, 0.0f);
    EXPECT_FLOAT_EQ(s.stiffness, 0.0f);
}

TEST(Spring, ParametrizedConstructor)
{
    Spring s(10.0f, 15.0f, 2.0f);
    EXPECT_FLOAT_EQ(s.initLength, 10.0f);
    EXPECT_FLOAT_EQ(s.finalLength, 15.0f);
    EXPECT_FLOAT_EQ(s.stiffness, 2.0f);
}