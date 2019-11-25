#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "adddialog.h"
#include "figures/shape.h"

uint hashFunc(QString string) {
    return qHash(string) % SIZE;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), hashMap(hashFunc), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    widget = new GraphWidget(this);
    setCentralWidget(widget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addFigureButton_clicked()
{
    auto dialog = new AddDialog(ui->classComboBox->currentText(), nullptr, this);
    connect(dialog, &AddDialog::itemChanged, this, &MainWindow::on_itemAdded);
    dialog->show();
}

void MainWindow::on_itemAdded(QGraphicsItem *item)
{
    Shape* shape = dynamic_cast<Shape*>(item);
    shape->setHashKey(ui->hashCodeEdit->text());
    widget->scene()->addItem(shape);
    hashMap.create(ui->hashCodeEdit->text(), item);
    item->update();
}
