#pragma once

namespace pavel {
    class Point {
        public:
            Point(double x = 0, double y = 0): x(x), y(y) {}
            Point(const Point &p): x(p.x), y(p.y) {}
            ~Point() = default;

            double getX() const { return x; }
            double getY() const { return y; }
            void setX(double x) { this->x = x; }
            void setY(double y) { this->y = y; }

        private:
            double x;
            double y;
    };
}
