#include "pentagram.h"
#include <cmath>
#include <QPainter>
#include <QStyleOption>
#include <QPolygonF>

#define _USE_MATH_DEFINES

QPentagram::QPentagram(double size)
    :size(size)
{

}

QRectF QPentagram::boundingRect() const
{
    qreal adjust = 2;
    return QRectF(-size - adjust, - size - adjust,
                  size * 2 + adjust, size * 2 + adjust);
}

QPainterPath QPentagram::shape() const
{
    QPainterPath path;
    path.addPolygon(getPolygon(getPoints()));
    return path;
}

void QPentagram::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::black));
    painter->setBrush(backgroundColor(option));
    auto path = getPath();
    auto polygon = getPolygon(path);
    painter->drawPolygon(polygon, Qt::WindingFill);
}

QString QPentagram::toString()
{
    return QString("Hello");
}

void QPentagram::print(std::ostream &o) const
{
    o << "Pentagram";
}

QVector<Point> QPentagram::getPoints() const
{
    auto points = QVector<Point>();
    for (int i = 0; i < 5; i++) {
        auto p = Point {size, 0};
        p.setPhi(i * M_PI * 2 / 5);
        points.push_back(p);
    }
    return points;
}

QVector<Point> QPentagram::getPath() const
{
    auto points = getPoints();
    return QVector<Point> {
        points[0],
        points[2],
        points[4],
        points[1],
        points[3],
        points[0]
    };
}
