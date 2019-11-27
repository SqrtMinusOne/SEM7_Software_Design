#include "pentagramtext.h"
#include <QJsonObject>

PentagramText::PentagramText(QString string, double size)
    :Pentagram(size), Text(string, size / 2)
{

}

QRectF PentagramText::boundingRect() const
{
    return Pentagram::boundingRect();
}

QPainterPath PentagramText::shape() const
{
    return Pentagram::shape();
}

void PentagramText::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Pentagram::paint(painter, option, widget);
    auto drawHashKey = getDrawHashKey();
    setDrawHashKey(false);
    Text::paint(painter, option, widget);
    setDrawHashKey(drawHashKey);
}

QJsonObject PentagramText::toJSON()
{
    QJsonObject params {};
    mergeJsons(params, Pentagram::toJSON()["params"].toObject());
    mergeJsons(params, Text::toJSON()["params"].toObject());
    QJsonObject object {
        {"className", "PentagramText"},
        {"params", params}
    };
    mergeJsons(object, Shape::toJSON());
    return object;
}

void PentagramText::print(std::ostream &o) const
{
    o << "PentagramText"; // TODO
}
