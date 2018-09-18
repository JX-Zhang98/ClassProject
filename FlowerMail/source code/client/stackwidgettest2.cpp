#include "stackwidgettest2.h"
#include "ui_stackwidgettest2.h"

StackWidgetTest2::StackWidgetTest2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StackWidgetTest2)
{
    ui->setupUi(this);
}

StackWidgetTest2::~StackWidgetTest2()
{
    delete ui;
}
