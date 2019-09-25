#include <cmath>
#include "atanSegment.h"

namespace pavel {
    AtanSegment::AtanSegment(Point bottomLeft, Point topRight, unsigned int precision)
        : precision(precision), borders(std::make_pair(topRight, bottomLeft)) {
        center = (topRight + bottomLeft) / 2;
    }

    std::pair<Point, Point> AtanSegment::getBorders() {
        return alignRect(getScaled(borders.first), getScaled(borders.second));
    }

    void AtanSegment::move(Point delta) {
        Shape::move(delta);
        borders.first += delta;
        borders.second += delta;
    }

    std::vector<Point> AtanSegment::getPath() {
        double x = atanStart;
        auto path = std::vector<Point>();
        auto boxDelta = borders.first - center;
        auto delta = (atanStop - atanStart) / precision;
        double xSize = boxDelta.getX();
        double ySize = boxDelta.getY();

        for (unsigned int i = 0; i <= precision; i++) {
            auto y = std::atan(x) * 2 / M_PI;
            auto p = Point {x * xSize, y * ySize} + center;
            p = getScaled(p);
            path.push_back(p);
            x += delta;
        }
        return path;
    }

    void AtanSegment::print(std::ostream &o) const {
        o << "AtanSegment {precision: " << precision
        << "; box:" << borders.second << " " << borders.first << "}";
    }

    unsigned int AtanSegment::getPrecision() const {
        return precision;
    }

    void AtanSegment::setPrecision(unsigned int newPrecision) {
        AtanSegment::precision = newPrecision;
    }

}
