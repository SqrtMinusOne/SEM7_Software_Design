#include "shape.h"

#include <QStyleOptionGraphicsItem>

Shape::Shape()
{
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
}

QColor Shape::backgroundColor(const QStyleOptionGraphicsItem *option)
{
    QColor col = QColor(Qt::yellow);
    if (option->state & QStyle::State_Sunken) {
        col = col.darker(120);
    }
    return col;
}

void Shape::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mousePressEvent(event);
}

void Shape::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

QPolygonF Shape::getPolygon(QVector<Point> points)
{
    auto polygon = QPolygonF();
    for (auto point: points){
        polygon << point;
    }
    return polygon;
}
