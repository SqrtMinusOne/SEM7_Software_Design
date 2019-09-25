#include <algorithm>
#include <cmath>
#define _USE_MATH_DEFINES

#include "point.hpp"
#include "shape.hpp"

namespace pavel {
    const Point &pavel::Shape::getCenter() const {
        return center;
    }

    double Shape::getAngle() const {
        return angle;
    }

    double Shape::getZoomCoef() const {
        return zoomCoef;
    }

    void Shape::move(Point delta) {
        center += delta;
    }

    void Shape::rotate(double newAngle) {
        angle = std::fmod(angle + newAngle, M_PI * 1);
    }

    void Shape::scale(double newCoef) {
        zoomCoef *= newCoef;
    }

    Point Shape::getScaled(Point p) {
        auto p2 = p - center;
        p2.setR(p2.getR() * getZoomCoef());
        p2.setPhi(p2.getPhi() + angle);
        p2 += center;
        return p2;
    }

    std::pair<Point, Point> Shape::alignRect(Point p1, Point p2) {
        return std::make_pair(
                Point(
                        std::max(p1.getX(), p2.getX()),
                        std::max(p1.getY(), p2.getY())
                ),
                Point(
                        std::min(p1.getX(), p2.getX()),
                        std::min(p1.getY(), p2.getY())
                )
        );
    }

}