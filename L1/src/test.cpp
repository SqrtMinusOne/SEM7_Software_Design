#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc32-c"
#pragma ide diagnostic ignored "cert-err58-cpp"

#include <ctime>
#include <iostream>
#include <random>
#include "gtest/gtest.h"

#include "point.h"
#include "pentagram.h"
#include "text.h"
#include "atanSegment.h"
#include "pentagramText.h"
#include "hashMap.h"


TEST(PointTest, BasicPointTest) {
    std::mt19937 gen(time(nullptr));
    std::uniform_real_distribution<> urd(-10, 10);
    auto x = urd(gen);
    auto y = urd(gen);

    Point p1 {x, y};
    ASSERT_EQ(p1.getX(), x);
    ASSERT_EQ(p1.getY(), y);
    ASSERT_GE(p1.getR(), 0);
    ASSERT_NEAR(p1.getPhi(), 0, M_PI);

    p1.setX(y);
    p1.setY(x);
    ASSERT_EQ(p1.getX(), y);
    ASSERT_EQ(p1.getY(), x);
}

TEST(PointTest, CopyPaste) {
    Point p1 {2, 3};
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

void checkBorders(Shape& figure) {
    auto [p2, p1] = figure.getBorders();
    for (Point& point : figure.getPath()) {
        ASSERT_LE(point.getX(), p1.getX());
        ASSERT_LE(point.getY(), p1.getY());

        ASSERT_GE(point.getX(),p2.getX());
        ASSERT_GE(point.getY(),p2.getY());
    }
}

void standartMoveSequence(Shape& figure) {
    ASSERT_NO_FATAL_FAILURE(checkBorders(figure));

    figure.move(Point(99, -200));
    ASSERT_NO_FATAL_FAILURE(checkBorders(figure));

    figure.rotate(M_PI / 3);
    figure.scale(14);
    ASSERT_NO_FATAL_FAILURE(checkBorders(figure));

    figure.scale(0.0001);
    ASSERT_NO_FATAL_FAILURE(checkBorders(figure));
}

TEST(ShapeTest, PentagramTest) {
    auto center = Point{2, 3};
    auto fig = Pentagram(center, 10);
    ASSERT_NO_FATAL_FAILURE(checkBorders(fig));

    auto [ap1, ap2] = fig.getBorders();
    fig.move(Point {2, 5});
    auto [bp1, bp2] = fig.getBorders();

    ASSERT_LT(ap1.getX(), bp1.getX());
    ASSERT_LT(ap2.getY(), bp2.getY());

    fig.rotate(M_PI * 0.42);
    fig.scale(13.4);
    auto [cp2, cp1] = fig.getBorders();
    ASSERT_NO_FATAL_FAILURE(checkBorders(fig));
    ASSERT_EQ(fig.getAngle(), M_PI*0.42);

    ASSERT_LT(cp2.getX(), bp2.getX());
    ASSERT_GT(cp1.getY(), bp1.getY());

    ASSERT_EQ(fig.getCenter(), center + Point(2, 5));
}

TEST(ShapeTest, TextTest){
    auto text = Text("Hello",
                            Point(0, 0),
                            Point(10, 10));
    ASSERT_EQ(text.getString(), "Hello");
    ASSERT_NO_FATAL_FAILURE(checkBorders(text));

    text.setString("Goodbye");
    ASSERT_EQ(text.getString(), "Goodbye");

    ASSERT_NO_FATAL_FAILURE(standartMoveSequence(text));

}

TEST(ShapeTest, AtanSegmentTest) {
    auto seg = AtanSegment(Point{0, 0}, Point{10, 10}, 0);
    ASSERT_NO_FATAL_FAILURE(checkBorders(seg));
    ASSERT_NO_FATAL_FAILURE(standartMoveSequence(seg));

    seg.setPrecision(20000);
    ASSERT_NO_FATAL_FAILURE(checkBorders(seg));
    ASSERT_EQ(seg.getPrecision(), 20000);
    seg.setPrecision(2);
    ASSERT_NO_FATAL_FAILURE(checkBorders(seg));
}



TEST(ContainerTest, InitTest) {
    auto m = HashMap<int, int>();
    m.create(15, 20);
    m.create(20, 30);
    m.create(30, 40);
    ASSERT_EQ(m.at(15), 20);
    ASSERT_EQ(m.at(20), 30);
    ASSERT_EQ(m.at(30), 40);
    int val;
    ASSERT_FALSE(m.get(16, val));
    ASSERT_TRUE(m.get(15, val));
    m.update(15, 25);
    ASSERT_EQ(m.at(15), 25);
    m.remove(15);
    ASSERT_FALSE(m.get(15, val));
}

TEST(ContainerTest, IteratorTest1) {
    auto m = HashMap<int, double>();
    m.create(1, 2);
    m.create(2, 3);

    auto iter = HashMapIterator<int, double>(m);
    while (!iter.end()) {
        ASSERT_NE(iter.value(), 0);
        ASSERT_NE(iter.key(), 0);
        ++iter;
    }
}

TEST(ContainerTest, IteratorTest2) {
    auto m = HashMap<int, double>();
    m.create(1, 2);
    m.create(2, 3);
    m.create(10, 4);
    m.create(20, 40);
    m.create(25, 45);

    auto it1 = m.begin();
    auto it2 = m.end();
    bool cmp = it1 == it2;
    ASSERT_FALSE(cmp);

    for (auto it = m.begin(); it != m.end(); it++) {
        ASSERT_NE(it.value(), 0);
        ASSERT_NE(it.key(), 0);
    }
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#pragma clang diagnostic pop