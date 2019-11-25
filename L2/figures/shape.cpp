#include "shape.h"

#include <QStyleOptionGraphicsItem>

Shape::Shape()
{
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
}

void Shape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (drawHashKey) {
        auto width = painter->fontMetrics().horizontalAdvance(hashKey);
        auto height = painter->fontMetrics().height();
        auto size = QSizeF(-width, -height);
        auto rect = QRectF(boundingRect().bottomRight(), size);
        rect = rect.normalized();

        painter->drawText(rect, Qt::AlignRight | Qt::AlignBottom, hashKey);
    }
}

QColor Shape::primaryColor(const QStyleOptionGraphicsItem *option)
{
    QColor col = QColor(color);
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

void Shape::setColor(const QColor &value)
{
    color = value;
}

bool Shape::getDrawHashKey() const
{
    return drawHashKey;
}

void Shape::setDrawHashKey(bool value)
{
    drawHashKey = value;
}

QString Shape::getHashKey() const
{
    return hashKey;
}

void Shape::setHashKey(const QString &value)
{
    hashKey = value;
    drawHashKey = true;
}
