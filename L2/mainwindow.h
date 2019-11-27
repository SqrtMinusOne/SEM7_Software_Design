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
    void addItem(QGraphicsItem* item, QString hash, QString className);
    void on_itemDelete(QString hash);
    void on_itemEdit(QString hash);
    void on_itemEdited(QGraphicsItem* item);

    void on_actionSave_triggered();

    void on_actionClear_triggered();

    void on_actionOpen_triggered();

    void on_actionNew_triggered();

private:
    HashMap<QString, QGraphicsItem*> hashMap;
    Ui::MainWindow *ui;
    GraphWidget* widget;
};

#endif // MAINWINDOW_H
