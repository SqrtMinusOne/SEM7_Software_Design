#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "graphwidget.h"
#include "hashMap.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private slots:
    void on_addFigureButton_clicked();
    void on_itemAdded(QGraphicsItem* item);
    void on_itemDelete(int row);

private:
    HashMap<QString, QGraphicsItem*> hashMap;
    Ui::MainWindow *ui;
    GraphWidget* widget;
};

#endif // MAINWINDOW_H
