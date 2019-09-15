#include <algorithm>

#include "point.hpp"

namespace pavel {
    void swap(Point &a, Point &b) {
        std::swap(a.x, b.x);
        std::swap(a.y, b.y);
    }

    Point &Point::operator=(Point p) {
        swap(*this, p);
        return *this;
    }

    Point::Point(Point &&p) noexcept {
        swap(*this, p);
    }

    Point & Point::operator/(double i)
    {
        x = x / i;
        y = y / i;
        return *this;
    }

    Point & Point::operator*(double i)
    {
        x = x * i;
        y = y * i;
        return *this;
    }

    bool operator==(const Point & a, const Point & b){
        return ((a.getX() == b.getX()) && (a.getY() == b.getY()));
    }

    Point operator+(const Point& p1, const Point& p2) {
        return Point(p1.getX() + p2.getX(), p1.getY() + p2.getY());
    }

    Point operator-(const Point& p1, const Point& p2) {
        return Point(p1.getX() - p2.getX(), p1.getY() - p2.getY());
    }

}
