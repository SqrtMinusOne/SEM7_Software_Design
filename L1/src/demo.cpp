#include <cmath>
#include <iostream>
#include <iomanip>
#include <atanSegment.h>
#include <text.h>

#include "shape.hpp"
#include "point.hpp"
#include "pentagram.h"
#include "colors.h"
#include "pentagramText.h"

#define OFFSET "    "

void box(const std::string& string, std::ostream& os,
        const std::string& boxColor = "\033[0m",
        const std::string& textColor = "\033[0m") {
    os << boxColor << "┌";
    for (int i = 0; i < string.length(); i++) {
        os << "─";
    }
    os << "┐" << std::endl;
    os << "│" << textColor << string << boxColor << "│" << std::endl;
    os << "└";
    for (int i = 0; i < string.length(); i++) {
        os << "─";
    }
    os << "┘" << std::endl << RESET;
}

std::string outPath(pavel::Shape& shape) {
    std::ostringstream os;
    os.precision(3);
    os << "[ ";
    for (auto &p : shape.getPath()) {
        os << p << " ";
    }
    os << "]";
    return os.str();
}

std::string offset(int offset) {
    std::string str;
    for (int i = 0; i < offset; i ++) {
        str += OFFSET;
    }
    return str;
}

void doStuffWithShape(pavel::Shape & shape, std::ostream& os) {
    os << BLUE << "Starting transformation sequence" << RESET << std::endl;
    os << offset(1) << "Path" << outPath(shape) << std::endl;
    auto move = pavel::Point {10, 20};
    os << offset(1) << GREEN << "Moving to " << move << RESET << std::endl;
    shape.move(move);
    os << offset(1) << "Path" << outPath(shape) << std::endl;

    double angle = 45.0 / 180.0 * M_PI;
    os << offset(2) << GREEN << "Rotating at 45 degrees" << RESET << std::endl;
    shape.rotate(angle);
    os << offset(2) << "Path" << outPath(shape) << std::endl;

    double scale = 12.5;
    os << offset(3) << GREEN << "Scaling " << scale << " times" << RESET << std::endl;
    shape.scale(scale);
    os << offset(3) << "Path" << outPath(shape) << std::endl;

    os << offset(3) << GREEN << "Scaling back" << RESET << std::endl;
    shape.scale(1 / scale);
    os << offset(3) << "Path" << outPath(shape) << std::endl;

    os << offset(2) << GREEN << "Rotating back" << RESET << std::endl;
    shape.rotate(-angle);
    os << offset(2) << "Path" << outPath(shape) << std::endl;

    os << offset(1)  << GREEN << "Moving back" << RESET << std::endl;
    shape.move(-move);
    os << offset(1) << "Path" << outPath(shape) << std::endl;
    os << BLUE << "Transformation sequence complete" << std::endl;
}

int main(int argc, char *argv[])
{
    std::cout.precision(3);
    box("          Korytov Pavel, 6304. LR 1           ", std::cout, RED);

    box("Pentagram test", std::cout, YELLOW);
    auto p = pavel::Pentagram(pavel::Point {0, 0}, 10);
    std::cout << p << std::endl;
    doStuffWithShape(p, std::cout);

    box("Atan test", std::cout, YELLOW);
    auto a = pavel::AtanSegment(pavel::Point{1, 1}, pavel::Point{10, 10}, 5);
    std::cout << a << std::endl;
    doStuffWithShape(a, std::cout);

    box("Text test", std::cout, YELLOW);
    auto t = pavel::Text("Hello, world", pavel::Point {-5, -5}, pavel::Point {5, 5});
    std::cout << t << std::endl;
    doStuffWithShape(t, std::cout);

    box("Pentagram with text test", std::cout, YELLOW);
    auto pt = pavel::PentagramText("Just fucking kill me", pavel::Point{1, 2}, 10);
    std::cout << pt << std::endl;
    doStuffWithShape(pt, std::cout);
}
