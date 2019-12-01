#include "shape.h"

#include <QStyleOptionGraphicsItem>
#include <QJsonObject>
#include <QJsonDocument>

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

QString Shape::toString()
{
    QJsonDocument doc(toJSON());
    return QString(doc.toJson(QJsonDocument::Compact));
}

QJsonObject Shape::toJSON()
{
    return QJsonObject {
        {"scenePos", QJsonObject {
                {"x", scenePos().x()},
                {"y", scenePos().y()},
            }
        }
    };
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

void Shape::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseMoveEvent(event);
    auto rect = scene()->sceneRect();
    if (x() < rect.x() - boundingRect().x()) {
        setPos(rect.x() - boundingRect().x(), y());
    } else if (x() > rect.width() + rect.x() - boundingRect().width() - boundingRect().x()) {
        setPos(rect.width() + rect.x() - boundingRect().width() - boundingRect().x(), y());
    }
    if (y() < rect.y() - boundingRect().y()) {
        setPos(x(), rect.y() - boundingRect().y());
    } else if (y() > rect.height() + rect.y() - boundingRect().height() - boundingRect().y()) {
        setPos(x(), rect.height() + rect.y() - boundingRect().height() - boundingRect().y());
    }
}

QPolygonF Shape::getPolygon(QVector<Point> points)
{
    auto polygon = QPolygonF();
    for (auto point: points){
        polygon << point;
    }
    return polygon;
}

void Shape::mergeJsons(QJsonObject &doc, const QJsonObject &second)
{
    for (auto key: second.keys()) {
        doc[key] = second[key];
    }
}

QColor Shape::getColor() const
{
    return color;
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
