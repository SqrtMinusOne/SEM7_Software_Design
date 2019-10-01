#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc32-c"
#pragma ide diagnostic ignored "cert-err58-cpp"

#include <ctime>
#include <iostream>
#include <random>
#include "gtest/gtest.h"

#include "point.hpp"
#include "pentagram.h"
#include "text.h"
#include "atanSegment.h"
#include "pentagramText.h"


TEST(PointTest, BasicPointTest) {
    std::mt19937 gen(time(nullptr));
    std::uniform_real_distribution<> urd(-10, 10);
    auto x = urd(gen);
    auto y = urd(gen);

    pavel::Point p1 {x, y};
    ASSERT_EQ(p1.getX(), x);
    ASSERT_EQ(p1.getY(), y);
    ASSERT_GE(p1.getR(), 0);
    ASSERT_NEAR(p1.getPhi(), M_PI, M_PI);

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
    ASSERT_EQ(p1.getPhi(), p2.getPhi());
    ASSERT_EQ(p1.getR(), p3.getR());

    ASSERT_TRUE(p1 == p2);
    auto p4 = p2 + p3;
    auto p5 = p3 * 2;
    ASSERT_TRUE(p4 == p5);
    ASSERT_GT(p4.getR(), p1.getR());
    ASSERT_GT(p5.getR(), p1.getR());
    ASSERT_EQ(p3.getPhi(), p5.getPhi());
}

void checkBorders(pavel::Shape& figure) {
    auto [p1, p2] = figure.getBorders();
    for (pavel::Point& point : figure.getPath()) {
        ASSERT_LE(point.getX(), p1.getX());
        ASSERT_LE(point.getY(), p1.getY());

        ASSERT_GE(point.getX(),p2.getX());
        ASSERT_GE(point.getY(),p2.getY());
    }
}

void standartMoveSequence(pavel::Shape& figure) {
    ASSERT_NO_FATAL_FAILURE(checkBorders(figure));

    figure.move(pavel::Point(99, -200));
    ASSERT_NO_FATAL_FAILURE(checkBorders(figure));

    figure.rotate(M_PI / 3);
    figure.scale(14);
    ASSERT_NO_FATAL_FAILURE(checkBorders(figure));

    figure.scale(0.0001);
    ASSERT_NO_FATAL_FAILURE(checkBorders(figure));
}

TEST(ShapeTest, PentagramTest) {
    auto center = pavel::Point{2, 3};
    auto fig = pavel::Pentagram(center, 10);
    ASSERT_NO_FATAL_FAILURE(checkBorders(fig));

    auto [ap1, ap2] = fig.getBorders();
    fig.move(pavel::Point {2, 5});
    auto [bp1, bp2] = fig.getBorders();

    ASSERT_LT(ap1.getX(), bp1.getX());
    ASSERT_LT(ap2.getY(), bp2.getY());

    fig.rotate(M_PI * 0.42);
    fig.scale(13.4);
    auto [cp1, cp2] = fig.getBorders();
    ASSERT_NO_FATAL_FAILURE(checkBorders(fig));
    ASSERT_EQ(fig.getAngle(), M_PI*0.42);

    ASSERT_LT(cp2.getX(), bp2.getX());
    ASSERT_GT(cp1.getY(), bp1.getY());

    ASSERT_EQ(fig.getCenter(), center + pavel::Point(2, 5));
}

TEST(ShapeTest, TextTest){
    auto text = pavel::Text("Hello",
                            pavel::Point(0, 0),
                            pavel::Point(10, 10));
    ASSERT_EQ(text.getString(), "Hello");
    ASSERT_NO_FATAL_FAILURE(checkBorders(text));

    text.setString("Goodbye");
    ASSERT_EQ(text.getString(), "Goodbye");

    ASSERT_NO_FATAL_FAILURE(standartMoveSequence(text));

}

TEST(ShapeTest, AtanSegmentTest) {
    auto seg = pavel::AtanSegment(pavel::Point{0, 0}, pavel::Point{10, 10}, 0);
    ASSERT_NO_FATAL_FAILURE(checkBorders(seg));
    ASSERT_NO_FATAL_FAILURE(standartMoveSequence(seg));

    seg.setPrecision(20000);
    ASSERT_NO_FATAL_FAILURE(checkBorders(seg));
    ASSERT_EQ(seg.getPrecision(), 20000);
    seg.setPrecision(2);
    ASSERT_NO_FATAL_FAILURE(checkBorders(seg));
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#pragma clang diagnostic pop