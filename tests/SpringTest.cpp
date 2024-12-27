#include <gtest/gtest.h>
#include "Spring.h"

TEST(SpringTest, ctr)
{
    Spring spr;
    EXPECT_FLOAT_EQ(spr.initialLength, 0.0f);
    EXPECT_FLOAT_EQ(spr.finalLength, 0.0f);
    EXPECT_FLOAT_EQ(spr.stiffness, 0.0f);
}
