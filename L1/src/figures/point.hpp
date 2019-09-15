#pragma once

namespace pavel {
    class Point {
        public:
            /* Constructors and copy */
            explicit Point(double x = 0, double y = 0): x(x), y(y) {}
            Point(const Point &p) = default;
            ~Point() = default;

            friend void swap(Point& a, Point& b);
            Point& operator=(Point p);
            Point(Point&& p) noexcept;

            /* Getters, setters */
            [[nodiscard]] double getX() const { return x; }
            [[nodiscard]] double getY() const { return y; }
            void setX(double x_) { x = x_; }
            void setY(double y_) { y = y_; }

            /* Arithmetic */
            Point& operator/(double i);
            Point& operator*(double i);

        private:
            double x{};
            double y{};
    };

    bool operator==(const Point& a, const Point& b);
    Point operator+(const Point& p1, const Point& p2);
    Point operator-(const Point& p1, const Point& p2);
}

