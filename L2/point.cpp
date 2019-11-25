#include "point.h"

#include <QtMath>

double Point::getPhi() const {
    return qAtan2(y(), x());
}

double Point::getR() const {
    return qSqrt(x()*x() + y()*y());
}

void Point::setR(double newR) {
    double phi = getPhi();
    setX(newR * qCos(phi));
    setY(newR * qSin(phi));
}

void Point::setPhi(double newPhi) {
    double r = getR();
    setX(r * qCos(newPhi));
    setY(r * qSin(newPhi));
}
