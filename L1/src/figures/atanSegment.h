#pragma once

#include "shape.h"

namespace pavel {
    class AtanSegment : public Shape {
    public:
        explicit AtanSegment(Point bottomLeft, Point topRight, unsigned int precision = 20);

        std::pair<Point, Point> getBorders() override;

        std::vector<Point> getPath() override;

        [[nodiscard]] unsigned int getPrecision() const;
        void setPrecision(unsigned int newPrecision);

        void move(Point delta) override;

    protected:
        void print(std::ostream &o) const override;

    private:
        unsigned int precision;
        std::pair<Point, Point> borders;
        double atanStart = -1;
        double atanStop = 1;
    };
}