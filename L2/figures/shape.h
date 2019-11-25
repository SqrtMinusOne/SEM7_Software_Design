#ifndef SHAPE_H
#define SHAPE_H

#include "graphwidget.h"
#include "point.h"
#include <QGraphicsItem>

class Shape : virtual public QGraphicsItem
{
public:
    explicit Shape();
    virtual ~Shape() override = default;

    // QGraphicsItem interface
    virtual QRectF boundingRect() const override = 0;
    virtual QPainterPath shape() const override = 0;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override = 0;

    friend std::ostream &operator<<(std::ostream &os, const Shape &shape);

    virtual QString toString() = 0;
protected:
    virtual QColor primaryColor(const QStyleOptionGraphicsItem* option);
    virtual void print(std::ostream &o) const = 0;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    static QPolygonF getPolygon(QVector<Point> points);
};

inline std::ostream &operator<<(std::ostream &os, const Shape &shape) {
    shape.print(os);
    return os;
}

#endif // SHAPE_H
