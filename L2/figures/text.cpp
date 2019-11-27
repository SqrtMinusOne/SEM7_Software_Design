#include "text.h"
#include <QStyleOptionGraphicsItem>
#include <QJsonObject>

Text::Text(QString string, double width)
    :string(string), width(width)
{
    height = width / string.length() * 8;
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
    Shape::paint(painter, option, widget);
    auto factor = width / painter->fontMetrics().horizontalAdvance(string);
    auto font = painter->font();
    if (string.length() == 1) {
        factor *= 0.5;
    }
    font.setPointSizeF(font.pointSizeF() * factor);
    height = painter->fontMetrics().height() * font.pointSizeF() / 5;
    QRectF rect(-width / 2, -height / 4, width, height / 2);

    painter->setFont(font);
    painter->setPen(QPen(textColor(option)));
    painter->drawText(rect, Qt::AlignHCenter | Qt::AlignVCenter, string);
    // painter->drawRect(rect);
}

void Text::print(std::ostream &o) const
{
    o << "Text"; // TODO
}

double Text::getHeight() const
{
    return height;
}

void Text::setHeight(double value)
{
    height = value;
}

QJsonObject Text::toJSON()
{
    QJsonObject object {
        {"className", "Text"},
        {"params", QJsonObject {
                {"string", string},
                {"width", width}
            }
        }
    };
    mergeJsons(object, Shape::toJSON());
    return object;
}

double Text::getWidth() const
{
    return width;
}

void Text::setWidth(double value)
{
    width = value;
}

QString Text::getString() const
{
    return string;
}

void Text::setString(const QString &value)
{
    string = value;
}

QColor Text::textColor(const QStyleOptionGraphicsItem *option)
{
    if (option->state & QStyle::State_Sunken) {
        return Qt::gray;
    }
    return Qt::black;
}
