#pragma once

#include <iostream>

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

    [[nodiscard]] double getR() const;
    [[nodiscard]] double getPhi() const;
    void setR(double newR);
    void setPhi(double newPhi);

    /* Arithmetic */
    Point& operator/(double i);
    Point& operator*(double i);
    Point& operator+=(Point p);
    Point& operator-=(Point p);
    Point& operator-();

    /* Stream */
    friend std::ostream& operator<< (std::ostream& os, const Point& p);
    friend std::istream& operator>> (std::istream& is, Point& p);

private:
    double x{};
    double y{};
};

bool operator==(const Point& a, const Point& b);
Point operator+(const Point& p1, const Point& p2);
Point operator-(const Point& p1, const Point& p2);

Point operator+(const Point& p1, double a);
Point operator-(const Point& p1, double a);

