#include <cmath>
#include <tuple>

#include "pentagram.h"

namespace pavel {
    Pentagram::Pentagram(Point center, double size): Shape(center), size(size) {}

    std::vector<Point> Pentagram::getPoints() {
        auto points = std::vector<Point>();
        for (int i = 0; i < 5; i++) {
            auto p = Point {size, 0};
            p.setPhi(i * M_PI * 2 / 5);
            p += center;
            p = getScaled(p);
            points.push_back(p);
        }
        return points;
    }

    std::pair<Point, Point> Pentagram::getBorders() {
        auto coef = size * zoomCoef;
        return std::make_pair(
            center - Point {coef, coef},
            center + Point {coef, coef}
        );
    }

    std::vector<Point> Pentagram::getPath() {
        auto points = getPoints();
        return std::vector<Point> {
            points[0],
            points[2],
            points[4],
            points[1],
            points[3],
            points[0]
        };
    }

    double Pentagram::getSize() const {
        return size * zoomCoef;
    }

    void Pentagram::print(std::ostream &o) const {
        o << "Pentagram: {center: " << getCenter() << "; size: " << getSize() << "}";
    }


}
