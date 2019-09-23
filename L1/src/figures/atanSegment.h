#pragma once

#include "shape.hpp"

namespace pavel {
    class AtanSegment : public Shape {
    public:
        explicit AtanSegment(Point topRight, Point bottomLeft, unsigned int precision = 20);

        std::pair<Point, Point> getBorders() override;

        std::vector<Point> getPath() override;

        [[nodiscard]] unsigned int getPrecision() const;
        void setPrecision(unsigned int precision);

        void move(Point delta) override;

    protected:
        void print(std::ostream &o) const override;

    private:
        unsigned int precision;
        std::pair<Point, Point> borders;
    };
}