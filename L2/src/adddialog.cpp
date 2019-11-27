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
    color = QColorDialog::getColor(color, this, "Выберите цвет");
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
    if (item != nullptr) {
        Shape* shape = dynamic_cast<Shape*>(item);
        color = shape->getColor();
        ui->showHashCodeCheckBox->setChecked(shape->getDrawHashKey());
    }
    auto splitter = new QSplitter(Qt::Vertical);
    ui->controlsLayout->addWidget(splitter);
}

void AddDialog::addPentagramControls()
{
    auto spinBox = new QDoubleSpinBox();
    spinBox->setRange(1, 1000);
    spinBox->setObjectName("sizeSpinBox");
    ui->controlsLayout->addWidget(new QLabel("Размер"));
    ui->controlsLayout->addWidget(spinBox);
    if (item == nullptr){
        spinBox->setValue(100);
    } else {
        Pentagram* p = dynamic_cast<Pentagram*>(item);
        spinBox->setValue(p->getSize());
    }
}

void AddDialog::addAtanSegmentControls()
{
    auto spinBox = new QSpinBox();
    spinBox->setRange(1, 1000);
    spinBox->setObjectName("precisionSpinBox");

    auto widthSpinBox = new QDoubleSpinBox();
    widthSpinBox->setRange(1, 1000);
    widthSpinBox->setObjectName("widthSpinBox");

    auto heigthSpinBox = new QDoubleSpinBox();
    widthSpinBox->setRange(1, 1000);
    heigthSpinBox->setObjectName("heightSpinBox");

    ui->controlsLayout->addWidget(new QLabel("Точность"));
    ui->controlsLayout->addWidget(spinBox);
    ui->controlsLayout->addWidget(new QLabel("Высота"));
    ui->controlsLayout->addWidget(heigthSpinBox);
    ui->controlsLayout->addWidget(new QLabel("Ширина"));
    ui->controlsLayout->addWidget(widthSpinBox);

    if (item == nullptr) {
        spinBox->setValue(100);
        widthSpinBox->setValue(100);
        heigthSpinBox->setValue(100);
    } else {
        AtanSegment* a = dynamic_cast<AtanSegment*>(item);
        spinBox->setValue(a->getPrecision());
        widthSpinBox->setValue(a->getWidth());
        heigthSpinBox->setValue(a->getHeight());
    }

}

void AddDialog::addTextControls()
{
    auto textEdit = new QLineEdit();
    textEdit->setObjectName("lineEdit");

    auto textWidth = new QDoubleSpinBox();
    textWidth->setObjectName("textWidthSpinBox");
    textWidth->setRange(1, 1000);

    ui->controlsLayout->addWidget(new QLabel("Текст"));
    ui->controlsLayout->addWidget(textEdit);
    ui->controlsLayout->addWidget(new QLabel("Ширина текста"));
    ui->controlsLayout->addWidget(textWidth);
    if (item == nullptr) {
        textWidth->setValue(40);
    } else {
        Text* t = dynamic_cast<Text*>(item);
        textWidth->setValue(t->getWidth());
        textEdit->setText(t->getString());
    }
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
        auto size = ui->controlBox->findChild<QDoubleSpinBox*>("sizeSpinBox")->value();
        Pentagram* p = dynamic_cast<Pentagram*>(item);
        p->setSize(size);
    }
    if (className == "AtanSegment") {
        auto precision = ui->controlBox->findChild<QSpinBox*>("precisionSpinBox")->value();
        auto width = ui->controlBox->findChild<QDoubleSpinBox*>("widthSpinBox")->value();
        auto height = ui->controlBox->findChild<QDoubleSpinBox*>("heightSpinBox")->value();
        AtanSegment* a = dynamic_cast<AtanSegment*>(item);
        a->setPrecision(precision);
        a->setWidth(width);
        a->setHeight(height);
    }
    if (className == "Text" || className == "PentagramText") {
        auto width = ui->controlBox->findChild<QDoubleSpinBox*>("textWidthSpinBox")->value();
        auto text = ui->controlBox->findChild<QLineEdit*>("lineEdit")->text();
        Text* t = dynamic_cast<Text*>(item);
        t->setString(text);
        t->setWidth(width);
    }
    Shape* s = dynamic_cast<Shape*>(item);
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
