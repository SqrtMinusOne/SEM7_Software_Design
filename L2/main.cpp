#include "mainwindow.h"
#include "exception.h"
#include <QApplication>
#include <QMessageBox>
#include <QTextStream>
#include <QString>

class MyApplication: virtual public QApplication {
    // QCoreApplication interface
public:
    using QApplication::QApplication;
    bool notify(QObject *receiver, QEvent *event) override {
        try {
            return QApplication::notify(receiver, event);
        } catch (Exception& e) {
            QMessageBox::critical(messageBoxWidget, "Исключение", e.toString());
            return true;
        }
        return false;
    }
    void setMessageBoxWidget(QWidget *value) {
        messageBoxWidget = value;
    }

private:
    QWidget* messageBoxWidget;
};

int main(int argc, char *argv[])
{
    MyApplication a(argc, argv);
    MainWindow w;
    w.show();
    a.setMessageBoxWidget(&w);
    return a.exec();
}
