#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    widget = new GraphWidget(this);
    setCentralWidget(widget);
}

MainWindow::~MainWindow()
{
    delete ui;
}
