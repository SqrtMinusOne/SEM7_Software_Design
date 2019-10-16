#include <cmath>
#include <memory>
#include <iostream>
#include <iomanip>

#include "atanSegment.h"
#include "text.h"
#include "myCli.h"

#include "shape.h"
#include "point.h"
#include "pentagram.h"
#include "colors.h"
#include "pentagramText.h"


std::string outPath(Shape& shape) {
    std::ostringstream os;
    os.precision(3);
    os << "[ ";
    for (auto &p : shape.getPath()) {
        os << p << " ";
    }
    os << "]";
    return os.str();
}

void doStuffWithShape(Shape & shape, std::ostream& os) {
    os << BLUE << "Starting transformation sequence" << RESET << std::endl;
    os << offset(1) << "Path" << outPath(shape) << std::endl;
    auto move = Point {10, 20};
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
    box("          Korytov Pavel, 6304. LR 1, Part 1           ", std::cout, RED);
    std::vector<std::shared_ptr<Shape>> arr {
            std::make_shared<Pentagram>(Pentagram(Point {0, 0}, 10)),
            std::make_shared<AtanSegment>(AtanSegment(Point{1, 1}, Point{10, 10}, 5)),
            std::make_shared<Text>(Text("Hello, world", Point {-5, -5}, Point {5, 5})),
            std::make_shared<PentagramText>(PentagramText("Text with pentagram", Point{1, 2}, 10))
    };
    for (auto &ptr: arr) {
        std::ostringstream s;
        s << *ptr.get();
        box(s.str(), std::cout, YELLOW);
        doStuffWithShape(*ptr.get(), std::cout);
    }
}
