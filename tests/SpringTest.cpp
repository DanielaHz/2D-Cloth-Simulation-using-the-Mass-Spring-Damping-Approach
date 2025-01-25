#include <gtest/gtest.h>
#include "Spring.h"

TEST(Spring, DefaultConstructor)
{
    Spring s;

    EXPECT_FLOAT_EQ(s.getRestLength(), 0.0f);
    EXPECT_FLOAT_EQ(s.getCurrentLength(), 0.0f);
    EXPECT_FLOAT_EQ(s.getStiffness(), 0.0f);
    EXPECT_EQ(s.getMass1(), nullptr);
    EXPECT_EQ(s.getMass2(), nullptr);
}

TEST(Spring, ParametrizedConstructor)
{
    std::shared_ptr<Mass> m1;
    std::shared_ptr<Mass> m2;

    Spring s(10.0f, 15.0f, 2.0f, m1, m2);

    EXPECT_FLOAT_EQ(s.getRestLength(), 10.0f);
    EXPECT_FLOAT_EQ(s.getCurrentLength(), 15.0f);
    EXPECT_FLOAT_EQ(s.getStiffness(), 2.0f);
    EXPECT_EQ(s.getMass1(), m1);
    EXPECT_EQ(s.getMass2(), m2);
}

TEST(Spring, getMassPosition)
{
    // Creating the references for Mass objects
    auto m1 = std::make_shared<Mass>(ngl::Vec3{4.0f, 5.0f, 0.0f}, ngl::Vec3{0.0f, 0.0f, 0.0f}, ngl::Vec3{20.0f, 10.0f, 0.0f}, ngl::Vec3{1.0f, 3.0f, 0.0f}, 1.0f, 1.0f, false);
    auto m2 = std::make_shared<Mass>(ngl::Vec3{8.0f, 9.0f, 0.0f}, ngl::Vec3{0.0f, 0.0f, 0.0f}, ngl::Vec3{25.0f, 15.0f, 0.0f}, ngl::Vec3{1.0f, 3.0f, 0.0f}, 1.0f, 1.0f, false);

    // Creating the spring with parameterized constructor
    Spring s(10.0f, 15.0f, 2.0f, m1, m2);

    // Get mass postions
    ngl::Vec3 massPos1 = s.getMassPosition(m1);
    ngl::Vec3 massPos2 = s.getMassPosition(m2);

    // Verify the positions of the masses attached to the spring
    ngl::Vec3 pos1{20.0f, 10.0f, 0.0f};
    ngl::Vec3 pos2{25.0f, 15.0f, 0.0f};

    EXPECT_EQ(massPos1, pos1);
    EXPECT_EQ(massPos2, pos2);
}

TEST(Spring, CalculateCurrentLength)
{
    // Creating the references for Mass objects
    auto m1 = std::make_shared<Mass>(ngl::Vec3{4.0f, 5.0f, 0.0f}, ngl::Vec3{0.0f, 0.0f, 0.0f}, ngl::Vec3{20.0f, 10.0f, 0.0f}, ngl::Vec3{1.0f, 3.0f, 0.0f}, 1.0f, 1.0f, false);
    auto m2 = std::make_shared<Mass>(ngl::Vec3{9.0f, 12.0f, 0.0f},ngl::Vec3{0.0f, 0.0f, 0.0f}, ngl::Vec3{25.0f, 15.0f, 0.0f}, ngl::Vec3{1.0f, 3.0f, 0.0f}, 1.0f, 1.0f, false);
    
    // Creating the spring with parameterized constructor
    Spring s(2.0f, 0.0f, 0.0f , m1, m2);
    float currentLen = s.calculateCurrentLength(m1, m2);

     // Positions of the masses
    ngl::Vec3 pos1 {20.0f, 10.0f, 0.0f};
    ngl::Vec3 pos2 {25.0f, 15.0f, 0.0f};

    ngl::Vec3 distance = pos2 - pos1;

    // Expected length is the magnitude of the distance vector
    float expectedLen = distance.length();

    EXPECT_FLOAT_EQ(currentLen, expectedLen);
}