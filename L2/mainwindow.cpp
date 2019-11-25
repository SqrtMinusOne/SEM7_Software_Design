#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "adddialog.h"
#include "figures/shape.h"

#include <QTableWidgetItem>
#include <QMessageBox>

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
    auto hash = ui->hashCodeEdit->text();
    shape->setHashKey(hash);
    widget->scene()->addItem(shape);
    hashMap.create(hash, item);
    item->update();

    auto newRow = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(newRow);
    ui->tableWidget->setItem(newRow, 0, new QTableWidgetItem(hash));
    ui->tableWidget->setItem(newRow, 1, new QTableWidgetItem(ui->classComboBox->currentText()));
    ui->tableWidget->setItem(newRow, 2, new QTableWidgetItem(shape->toString()));

    QWidget* controlWidget = new QWidget();
    QHBoxLayout* layout = new QHBoxLayout();
    QPushButton* deleteButton = new QPushButton("Del");
    QPushButton* editButton = new QPushButton("Edit");
    layout->addWidget(deleteButton);
    layout->addWidget(editButton);
    layout->setAlignment(Qt::AlignCenter);
    layout->setContentsMargins(0, 0, 0, 0);
    controlWidget->setLayout(layout);
    ui->tableWidget->setCellWidget(newRow, 3, controlWidget);

    connect(deleteButton, &QPushButton::clicked, this, [=](){ this->on_itemDelete(newRow); });
}

void MainWindow::on_itemDelete(int row)
{
    auto hash = ui->tableWidget->takeItem(row, 0)->text();
    QGraphicsItem* item = hashMap.at(hash);

    widget->scene()->removeItem(item);
    hashMap.remove(hash);
    ui->tableWidget->removeRow(row);
}
