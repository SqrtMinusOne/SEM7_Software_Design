#ifndef PENTAGRAMTEXT_H
#define PENTAGRAMTEXT_H

#include "figures/pentagram.h"
#include "figures/text.h"

class PentagramText: virtual public Pentagram, virtual public Text
{
public:
    PentagramText(QString string, double size = 100);

    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const override;
    virtual QPainterPath shape() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    // Shape interface
    virtual QString toString() override;

protected:
    virtual void print(std::ostream &o) const override;
};

#endif // PENTAGRAMTEXT_H
