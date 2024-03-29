#ifndef SHAPE_H
#define SHAPE_H

#include "graphwidget.h"
#include "point.h"
#include <QGraphicsItem>
#include <QJsonObject>

class Shape : virtual public QGraphicsItem
{
public:
    explicit Shape();
    virtual ~Shape() override = default;

    // QGraphicsItem interface
    virtual QRectF boundingRect() const override = 0;
    virtual QPainterPath shape() const override = 0;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    friend std::ostream &operator<<(std::ostream &os, const Shape &shape);

    [[nodiscard]] virtual QString toString();
    [[nodiscard]] virtual QJsonObject toJSON();
    [[nodiscard]] QString getHashKey() const;
    void setHashKey(const QString &value);

    [[nodiscard]] bool getDrawHashKey() const;
    void setDrawHashKey(bool value);

    void setColor(const QColor &value);
    QColor getColor() const;

protected:
    virtual QColor primaryColor(const QStyleOptionGraphicsItem* option);
    virtual void print(std::ostream &o) const = 0;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

    static QPolygonF getPolygon(QVector<Point> points);
    static void mergeJsons(QJsonObject& doc, const QJsonObject& second);

private:
    QColor color = Qt::yellow;
    QString hashKey;
    bool drawHashKey = true;

};

inline std::ostream &operator<<(std::ostream &os, const Shape &shape) {
    shape.print(os);
    return os;
}

#endif // SHAPE_H
