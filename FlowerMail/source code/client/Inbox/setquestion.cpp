#include "setquestion.h"
#include "ui_setquestion.h"

setquestion::setquestion(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::setquestion)
{
    ui->setupUi(this);
}

setquestion::~setquestion()
{
    delete ui;
}
