#include <QColorDialog>
#include <QSpinBox>
#include <QSplitter>
#include <QLineEdit>
#include <tuple>

#include "adddialog.h"
#include "ui_adddialog.h"
#include "figures/atansegment.h"
#include "figures/pentagram.h"
#include "figures/pentagramtext.h"
#include "figures/text.h"

AddDialog::AddDialog(QString className, QGraphicsItem *item, QWidget *parent)
    :QDialog(parent), ui(new Ui::AddDialog), item(item),  className(className)
{
    ui->setupUi(this);
    addControls();
}

AddDialog::~AddDialog()
{
    delete ui;
}

void AddDialog::on_selectColorButton_clicked()
{
    color = QColorDialog::getColor(Qt::yellow, this, "Выберите цвет");
}

void AddDialog::addControls()
{
    if (className == "Pentagram") {
        addPentagramControls();
    } else if (className == "AtanSegment") {
        addAtanSegmentControls();
    } else if (className == "Text"){
        addTextControls();
    } else if (className == "PentagramText") {
        addPentagramControls();
        addTextControls();
    }
    auto splitter = new QSplitter(Qt::Vertical);
    ui->controlsLayout->addWidget(splitter);
}

void AddDialog::addPentagramControls()
{
    auto spinBox = new QSpinBox();
    spinBox->setMinimum(1);
    spinBox->setObjectName("sizeSpinBox");
    spinBox->setValue(100);
    ui->controlsLayout->addWidget(new QLabel("Размер"));
    ui->controlsLayout->addWidget(spinBox);
}

void AddDialog::addAtanSegmentControls()
{
    auto spinBox = new QSpinBox();
    spinBox->setMinimum(1);
    spinBox->setValue(100);
    spinBox->setObjectName("precisionSpinBox");

    auto widthSpinBox = new QDoubleSpinBox();
    widthSpinBox->setMinimum(1);
    widthSpinBox->setValue(100);
    widthSpinBox->setObjectName("widthSpinBox");

    auto heigthSpinBox = new QDoubleSpinBox();
    heigthSpinBox->setMinimum(1);
    heigthSpinBox->setValue(100);
    heigthSpinBox->setObjectName("heightSpinBox");

    ui->controlsLayout->addWidget(new QLabel("Точность"));
    ui->controlsLayout->addWidget(spinBox);
    ui->controlsLayout->addWidget(new QLabel("Высота"));
    ui->controlsLayout->addWidget(heigthSpinBox);
    ui->controlsLayout->addWidget(new QLabel("Ширина"));
    ui->controlsLayout->addWidget(widthSpinBox);

}

void AddDialog::addTextControls()
{
    auto textEdit = new QLineEdit();
    textEdit->setObjectName("lineEdit");

    auto textWidth = new QDoubleSpinBox();
    textWidth->setObjectName("textWidthSpinBox");
    textWidth->setValue(40);

    ui->controlsLayout->addWidget(new QLabel("Текст"));
    ui->controlsLayout->addWidget(textEdit);
    ui->controlsLayout->addWidget(new QLabel("Ширина текста"));
    ui->controlsLayout->addWidget(textWidth);
}

QGraphicsItem *AddDialog::makeItem()
{
    if (className == "Pentagram"){
        return new Pentagram();
    } else if (className == "AtanSegment") {
        return new AtanSegment();
    } else if (className == "Text") {
        return new Text();
    } else {
        return new PentagramText();
    }
}

void AddDialog::setItemValues()
{
    if (className == "Pentagram" || className == "PentagramText"){
        auto size = ui->controlBox->findChild<QSpinBox*>("sizeSpinBox")->value();
        Pentagram* p = dynamic_cast<Pentagram*>(item);
        p->setSize(size);
    } else if (className == "AtanSegment") {
        auto precision = ui->controlBox->findChild<QSpinBox*>("precisionSpinBox")->value();
        auto width = ui->controlBox->findChild<QDoubleSpinBox*>("widthSpinBox")->value();
        auto height = ui->controlBox->findChild<QDoubleSpinBox*>("heightSpinBox")->value();
        AtanSegment* a = dynamic_cast<AtanSegment*>(item);
        a->setPrecision(precision);
        a->setWidth(width);
        a->setHeight(height);
    } else if (className == "Text" || className == "PentagramText") {
        auto width = ui->controlBox->findChild<QDoubleSpinBox*>("textWidthSpinBox")->value();
        auto text = ui->controlBox->findChild<QLineEdit*>("lineEdit")->text();
        Text* t = dynamic_cast<Text*>(item);
        t->setString(text);
        t->setWidth(width);
    }
    Shape * s = dynamic_cast<Shape*>(item);
    s->setColor(color);
    s->setDrawHashKey(ui->showHashCodeCheckBox->isChecked());
}

void AddDialog::on_buttonBox_accepted()
{
    if (item == nullptr) {
        item = makeItem();
    }
    setItemValues();
    emit itemChanged(item);
    close();
}
