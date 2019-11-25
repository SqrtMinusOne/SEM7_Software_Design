#ifndef TEXT_H
#define TEXT_H

#include "shape.h"

class Text : virtual public Shape
{
public:
    explicit Text(QString string = "", double width = 40);

    // QGraphicsItem interface
    virtual QRectF boundingRect() const override;
    virtual QPainterPath shape() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    // Shape interface
    virtual QString toString() override;

    [[nodiscard]] QString getString() const;
    void setString(const QString &value);

    [[nodiscard]] double getWidth() const;
    void setWidth(double value);

    [[nodiscard]] double getHeight() const;
    void setHeight(double value);

protected:
    virtual void print(std::ostream &o) const override;

    QString string;
    double width;
    double height;

private:
   QColor textColor(const QStyleOptionGraphicsItem* option);

};

#endif // TEXT_H
