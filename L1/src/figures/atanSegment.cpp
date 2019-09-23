#include <cmath>
#include "atanSegment.h"

namespace pavel {
    AtanSegment::AtanSegment(Point topRight, Point bottomLeft, unsigned int precision)
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
        double x = 0;
        auto path = std::vector<Point>();
        auto delta = borders.first - center;
        double xSize = delta.getX();
        double ySize = delta.getY();
        for (unsigned int i = 0; i <= precision; i++) {
            auto y = std::atan(x) * 2 / M_PI;
            auto p = Point {x * xSize, y * ySize} + center;
            p = getScaled(p);
            path.push_back(p);
        }
        return path;
    }

    void AtanSegment::print(std::ostream &o) const {
        o << "AtanSegment {precision:" << precision << "; center:" << center << "}";
    }

    unsigned int AtanSegment::getPrecision() const {
        return precision;
    }

    void AtanSegment::setPrecision(unsigned int precision) {
        AtanSegment::precision = precision;
    }

}
