#include "pentagram.h"
#include <cmath>
#include <QPainter>
#include <QStyleOption>
#include <QPolygonF>

Pentagram::Pentagram(double size)
    :size(size)
{

}

QRectF Pentagram::boundingRect() const
{
    qreal adjust = 2;
    return QRectF(-size - adjust, - size - adjust,
                  size * 2 + adjust, size * 2 + adjust);
}

QPainterPath Pentagram::shape() const
{
    QPainterPath path;
    path.addPolygon(getPolygon(getPoints()));
    return path;
}

void Pentagram::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Shape::paint(painter, option, widget);
    painter->setPen(QPen(Qt::black));
    painter->setBrush(primaryColor(option));
    auto path = getPath();
    auto polygon = getPolygon(path);
    painter->drawPolygon(polygon, Qt::WindingFill);
}

QString Pentagram::toString()
{
    return QString("Hello");
}

void Pentagram::print(std::ostream &o) const
{
    o << "Pentagram";
}

double Pentagram::getSize() const
{
    return size;
}

void Pentagram::setSize(double value)
{
    size = value;
}

QVector<Point> Pentagram::getPoints() const
{
    auto points = QVector<Point>();
    for (int i = 0; i < 5; i++) {
        auto p = Point {size, 0};
        p.setPhi(i * M_PI * 2 / 5);
        points.push_back(p);
    }
    return points;
}

QVector<Point> Pentagram::getPath() const
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
