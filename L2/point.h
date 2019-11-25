#ifndef POINT_H
#define POINT_H

#include <QPointF>
#include <iostream>

class Point : public QPointF
{
    using QPointF::QPointF;
public:
    [[nodiscard]] double getR() const;
    [[nodiscard]] double getPhi() const;
    void setR(double newR);
    void setPhi(double newPhi);

    friend std::ostream& operator<< (std::ostream& os, const Point& p);
};

#endif // POINT_H
