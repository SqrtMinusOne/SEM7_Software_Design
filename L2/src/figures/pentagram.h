#ifndef PENTAGRAM_H
#define PENTAGRAM_H

#include <QVector>
#include "figures/shape.h"
#include "point.h"

class Pentagram : virtual public Shape
{
public:
    Pentagram(double size = 100);

    // QGraphicsItem interface
    virtual QRectF boundingRect() const override;
    virtual QPainterPath shape() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    double getSize() const;
    void setSize(double value);

    virtual QJsonObject toJSON() override;

protected:
    virtual void print(std::ostream &o) const override;
    double size;

private:
    [[nodiscard]] QVector<Point> getPath() const;
    [[nodiscard]] QVector<Point> getPoints() const;
};

#endif // PENTAGRAM_H
