#pragma once

#include <tuple>
#include <vector>
#include <utility>
#include <ostream>
#include "point.hpp"

namespace pavel {
    class Shape {
    public:
        explicit Shape(Point center = Point {0, 0}): center(std::move(center)) {}
        virtual ~Shape() = default;
        [[nodiscard]] virtual std::pair<Point, Point> getBorders() = 0;
        [[nodiscard]] virtual std::vector<Point> getPath() = 0;

        virtual void move(Point delta);
        virtual void rotate(double newAngle);
        virtual void scale(double newCoef);

        [[nodiscard]] const Point &getCenter() const;
        [[nodiscard]] double getAngle() const;
        [[nodiscard]] double getZoomCoef() const;

        friend std::ostream &operator<<(std::ostream &os, const Shape &shape);

    protected:
        virtual void print(std::ostream &o) const = 0;

        Point getScaled(Point p);
        static std::pair<Point, Point> alignRect(Point p1, Point p2);
        Point center;
        double angle = 0;
        double zoomCoef = 1;
    };

    inline std::ostream &operator<<(std::ostream &os, const Shape &shape) {
        shape.print(os);
        return os;
    }
}

