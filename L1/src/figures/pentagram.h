#pragma once

#include <ostream>
#include "point.hpp"
#include "shape.hpp"

namespace pavel {
    class Pentagram: public Shape {
    public:
        explicit Pentagram(Point center = Point {0, 0}, double size = 1);

        std::pair<Point, Point> getBorders() override;

        std::vector<Point> getPath() override;

        [[nodiscard]] double getSize() const;
    private:

        void print(std::ostream &o) const override;
        [[nodiscard]] std::vector<Point> getPoints();
        double size;
    };
}
