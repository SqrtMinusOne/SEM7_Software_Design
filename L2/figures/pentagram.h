#ifndef PENTAGRAM_H
#define PENTAGRAM_H

#include <QVector>
#include "figures/shape.h"
#include "point.h"

class QPentagram : public Shape
{
public:
    QPentagram(double size = 1);

public:
    // QGraphicsItem interface
    virtual QRectF boundingRect() const override;
    virtual QPainterPath shape() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    virtual QString toString() override;
protected:
    virtual void print(std::ostream &o) const override;
    double size;

private:
    [[nodiscard]] QVector<Point> getPath() const;
    [[nodiscard]] QVector<Point> getPoints() const;

    // Shape interface
};

#endif // PENTAGRAM_H
