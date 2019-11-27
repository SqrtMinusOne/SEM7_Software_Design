#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>
#include <QGraphicsItem>

namespace Ui {
class AddDialog;
}

class AddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddDialog(QString className, QGraphicsItem *item = nullptr, QWidget *parent = nullptr);
    ~AddDialog();

signals:
    void itemChanged(QGraphicsItem* item);

private slots:
    void on_selectColorButton_clicked();

    void on_buttonBox_accepted();

private:
    void addControls();
    void addPentagramControls();
    void addAtanSegmentControls();
    void addTextControls();

    [[nodiscard]] QGraphicsItem *makeItem();
    void setItemValues();
    
    Ui::AddDialog *ui;
    QColor color = Qt::yellow;
    QGraphicsItem* item;
    QString className;
};

#endif // ADDDIALOG_H
