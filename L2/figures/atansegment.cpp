#include "atansegment.h"
#include <QJsonObject>
#include <QtMath>
#include <QStyleOptionGraphicsItem>
#include <cmath>


AtanSegment::AtanSegment(uint precision, double width, double height)
    :precision(precision), width(width), height(height)
{

}

QRectF AtanSegment::boundingRect() const
{
    qreal adjust = 2;
    return QRectF(-width / 2 - adjust, -height / 2 - adjust,
                  width + adjust, height + adjust);
}

QPainterPath AtanSegment::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void AtanSegment::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Shape::paint(painter, option, widget);
    auto points = getPath();
    QBrush brush(primaryColor(option));
    QPen pen(brush, lineWidth);
    painter->setPen(pen);
    painter->setBrush(brush);
    for (int i = 0; i < points.length() - 1; i++) {
        painter->drawLine(points[i], points[i+1]);
    }
    // painter->drawRect(boundingRect());
}

QJsonObject AtanSegment::toJSON()
{
    QJsonObject object {
        {"className", "AtanSegment"},
        {"params", QJsonObject {
                {"precision", (int)precision},
                {"width", width},
                {"height", height}
            }
        }
    };
    mergeJsons(object, Shape::toJSON());
    return object;
}

void AtanSegment::print(std::ostream &o) const
{
    o << "AtanSegment"; // TODO
}

QVector<Point> AtanSegment::getPath() const
{
    auto path = QVector<Point>();
    auto x = atanStart;
    auto delta = (atanStop - atanStart) / precision;

    for (uint i = 0; i < precision; i++) {
        auto y = qAtan(x) * 2 / M_PI;
        auto p = Point(x * width / 2, y * height / 2);
        path.push_back(p);
        x += delta;
    }
    return path;
}

double AtanSegment::getHeight() const
{
    return height;
}

void AtanSegment::setHeight(double value)
{
    height = value;
}

double AtanSegment::getWidth() const
{
    return width;
}

void AtanSegment::setWidth(double value)
{
    width = value;
}

uint AtanSegment::getPrecision() const
{
    return precision;
}

void AtanSegment::setPrecision(const uint &value)
{
    precision = value;
}

QColor AtanSegment::primaryColor(const QStyleOptionGraphicsItem *option)
{
    if (option->state & QStyle::State_Sunken) {
        return Qt::black;
    }
    return Qt::blue;
}
