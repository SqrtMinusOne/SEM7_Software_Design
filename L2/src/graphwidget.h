#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QGraphicsView>

class GraphWidget : public QGraphicsView
{
    Q_OBJECT
public:
    GraphWidget(QWidget* parent = nullptr);
    [[nodiscard]] QPointF centerPos();
    void setSceneSize();

public slots:
    void zoomIn();
    void zoomOut();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void drawBackground(QPainter *painter, const QRectF &rect) override;
    void scaleView(qreal scaleFactor);
};

#endif // GRAPHWIDGET_H
