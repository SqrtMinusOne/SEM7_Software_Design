#include <algorithm>
#include <cmath>

#include "point.h"

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

    std::ostream & operator<<(std::ostream & os, const Point& p)
    {
        os << "(" << p.x << "," << p.y << ")";
        return os;
    }

    std::istream & operator>> (std::istream & is, Point& p)
    {
        is >> p.x >> p.y;
        return is;
    }

    Point &Point::operator+=(Point p) {
        x = x + p.getX();
        y = y + p.getY();
        return *this;
    }

    Point &Point::operator-=(Point p) {
        x = x - p.getX();
        y = y - p.getY();
        return *this;
    }

    double Point::getR() const {
        return std::sqrt(x*x + y*y);
    }

    double Point::getPhi() const {
        // if ((x == 0) && (y > 0)) return M_PI/2;
        // if ((x == 0) && (y < 0)) return 3*M_PI/2;
        // if ((x > 0) && (y >= 0)) return std::atan(y/x);
        // if ((x > 0) && (y < 0)) return std::atan(y/x) + 2*M_PI;
        // if (x < 0) return std::atan(y/x) + M_PI;
        // if (x > 0) return std::atan2(y, x);
        // if ((x < 0) && (y >= 0)) return std::atan2(y, x) + M_PI;
        // if ((x < 0) && (y < 0)) return std::atan2(y, x) - M_PI;
        // if ((x == 0) && (y > 0)) return M_PI / 2;
        // if ((x == 0) && (y < 0)) return -M_PI / 2;
        return std::atan2(y, x);
    }

    void Point::setR(double newR) {
        double phi = getPhi();
        x = newR * std::cos(phi);
        y = newR * std::sin(phi);
    }

    void Point::setPhi(double newPhi) {
        double r = getR();
        x = r * std::cos(newPhi);
        y = r * std::sin(newPhi);
    }

    Point &Point::operator-() {
        x = -x;
        y = -y;
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

    Point operator+(const Point& p1, double a) {
        return Point{p1.getX() + a, p1.getY() + a};
    }
    Point operator-(const Point& p1, double a) {
        return Point {p1.getX() - a, p1.getY() - a};
    }
}
