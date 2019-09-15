#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc32-c"
#pragma ide diagnostic ignored "cert-err58-cpp"

#include <ctime>
#include <iostream>
#include <random>
#include "gtest/gtest.h"

#include "point.hpp"


TEST(PointTest, BasicPointTest) {
    std::mt19937 gen(time(nullptr));
    std::uniform_real_distribution<> urd(-10, 10);
    auto x = urd(gen);
    auto y = urd(gen);

    pavel::Point p1 {x, y};
    ASSERT_EQ(p1.getX(), x);
    ASSERT_EQ(p1.getY(), y);

    p1.setX(y);
    p1.setY(x);
    ASSERT_EQ(p1.getX(), y);
    ASSERT_EQ(p1.getY(), x);
}

TEST(PointTest, CopyPaste) {
    pavel::Point p1 {2, 3};
    auto p2 = p1;
    auto p3(p2);

    ASSERT_EQ(p1.getX(), p2.getX());
    ASSERT_EQ(p2.getX(), p3.getX());

    ASSERT_TRUE(p1 == p2);
    auto p4 = p2 + p3;
    auto p5 = p3 * 2;
    ASSERT_TRUE(p4 == p5);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#pragma clang diagnostic pop