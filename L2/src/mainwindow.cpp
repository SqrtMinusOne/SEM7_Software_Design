#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "adddialog.h"
#include "figures/shape.h"
#include "figures/pentagram.h"
#include "figures/atansegment.h"
#include "figures/pentagramtext.h"
#include "figures/text.h"

#include <QFileDialog>
#include <QJsonDocument>
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
    dialog->setAttribute(Qt::WA_DeleteOnClose, true);
    dialog->show();
}

void MainWindow::on_itemAdded(QGraphicsItem *item)
{
    auto hash = ui->hashCodeEdit->text();
    addItem(item, hash, ui->classComboBox->currentText());
}

void MainWindow::addItem(QGraphicsItem *item, QString hash, QString className)
{
    hashMap.create(hash, item);

    Shape* shape = dynamic_cast<Shape*>(item);
    shape->setHashKey(hash);
    widget->scene()->addItem(shape);
    shape->setPos(widget->centerPos());
    shape->update();

    auto newRow = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(newRow);
    ui->tableWidget->setItem(newRow, 0, new QTableWidgetItem(hash));
    ui->tableWidget->setItem(newRow, 1, new QTableWidgetItem(className));
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

    connect(deleteButton, &QPushButton::clicked, this, [=](){ this->on_itemDelete(hash); });
    connect(editButton, &QPushButton::clicked, this, [=](){ this->on_itemEdit(hash); });
    ui->hashCodeEdit->clear();
    widget->scene()->update();
}

void MainWindow::on_itemDelete(QString hash)
{
    QGraphicsItem* item = hashMap.at(hash);

    widget->scene()->removeItem(item);
    hashMap.remove(hash);
    for (int i = 0; i < ui->tableWidget->rowCount(); i++) {
        if (ui->tableWidget->item(i, 0)->text() == hash) {
            ui->tableWidget->removeRow(i);
            break;
        }
    }
}

void MainWindow::on_itemEdit(QString hash)
{
    QGraphicsItem* item = hashMap.at(hash);

    auto dialog = new AddDialog(ui->classComboBox->currentText(), item, this);
    connect(dialog, &AddDialog::itemChanged, this, &MainWindow::on_itemEdited);
    dialog->setAttribute(Qt::WA_DeleteOnClose, true);
    dialog->show();
}

void MainWindow::on_itemEdited(QGraphicsItem *item)
{
    item->update();
    widget->scene()->update();
}

void MainWindow::on_actionSave_triggered()
{
    QJsonObject object;
    for (auto it = hashMap.begin(); it <= hashMap.end(); it++){
        Shape* shape = dynamic_cast<Shape*>(it.value());
        object[it.key()] = shape->toJSON();
    }
    QJsonDocument doc(object);

    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить", "data.json", "JSON (*.json)");
    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    file.write(doc.toJson());
    file.close();
}

void MainWindow::on_actionClear_triggered()
{
    ui->tableWidget->setRowCount(0);
    widget->scene()->clear();
    hashMap.clear();
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Открыть файл", "", "JSON (*.json)");
    QFile file(fileName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonObject object = doc.object();

    on_actionClear_triggered();

    for (auto key: object.keys()) {
        Shape* shape = nullptr;
        auto doc = object[key].toObject();
        auto params = doc["params"].toObject();
        auto scenePos = doc["scenePos"].toObject();
        if (doc["className"] == "Pentagram") {
            shape = new Pentagram(params["size"].toDouble());
        } else if (doc["className"] == "PentagramText") {
            shape = new PentagramText(params["string"].toString(), params["size"].toDouble());
        } else if (doc["className"] == "Text") {
            shape = new Text(params["string"].toString(), params["width"].toDouble());
        } else if (doc["className"] == "AtanSegment") {
            shape = new AtanSegment(params["precision"].toInt(),
                    params["width"].toDouble(),
                    params["height"].toDouble());
        }
        if (shape != nullptr) {
            addItem(shape, key, doc["className"].toString());
            shape->setPos(scenePos["x"].toDouble(), scenePos["y"].toDouble());
        }
    }
}

void MainWindow::on_actionNew_triggered()
{
    MainWindow* w = new MainWindow();
    w->setAttribute(Qt::WA_DeleteOnClose, true);
    w->show();
}
