#ifndef ATANSEGMENT_H
#define ATANSEGMENT_H

#include "shape.h"

class AtanSegment : virtual public Shape
{
public:
    explicit AtanSegment(uint precision = 100, double width = 100, double height = 100);

    // QGraphicsItem interface
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    // Shape interface
    QString toString() override;

protected:
    void print(std::ostream &o) const override;

private:
    [[nodiscard]] QVector<Point> getPath() const;

    uint precision;
    double width;
    double height;

    double atanStart = -1;
    double atanStop = 1;
    double lineWidth = 1;

    // Shape interface
protected:
    QColor primaryColor(const QStyleOptionGraphicsItem *option) override;
};

#endif // ATANSEGMENT_H
