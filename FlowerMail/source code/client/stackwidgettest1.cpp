#include "stackwidgettest1.h"
#include "ui_stackwidgettest1.h"

StackWidgetTest1::StackWidgetTest1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StackWidgetTest1)
{
    ui->setupUi(this);
}

StackWidgetTest1::~StackWidgetTest1()
{
    delete ui;
}
