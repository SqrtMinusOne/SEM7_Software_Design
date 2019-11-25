#include "text.h"
#include <QStyleOptionGraphicsItem>

Text::Text(QString string, double width)
    :string(string), width(width)
{
    height = width / string.length() * 2;
}

QRectF Text::boundingRect() const
{
    qreal adjust = 2;
    return QRectF(-adjust - width / 2, -adjust - height / 2,
                  width + adjust, height + adjust);
}

QPainterPath Text::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void Text::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    auto factor = width / painter->fontMetrics().horizontalAdvance(string);
    height = painter->fontMetrics().height();
    auto font = painter->font();
    if (string.length() == 1) {
        factor *= 0.5;
    }
    QRectF rect(-width / 2, -height / 2, width, height);
    font.setPointSizeF(font.pointSizeF() * factor);
    painter->setFont(font);
    painter->setPen(QPen(textColor(option)));
    painter->drawText(rect, Qt::AlignHCenter | Qt::AlignVCenter, string);
    // painter->drawRect(rect);
}

QString Text::toString()
{
    return QString("Hello2"); // TODO
}

void Text::print(std::ostream &o) const
{
    o << "Text"; // TODO
}

QColor Text::textColor(const QStyleOptionGraphicsItem *option)
{
    if (option->state & QStyle::State_Sunken) {
        return Qt::gray;
    }
    return Qt::black;
}
