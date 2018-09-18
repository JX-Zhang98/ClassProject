#include "changepsdwithlast.h"
#include "ui_changepsdwithlast.h"

ChangePsdWithLast::ChangePsdWithLast(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChangePsdWithLast)
{
    ui->setupUi(this);
}

ChangePsdWithLast::~ChangePsdWithLast()
{
    delete ui;
}
void ChangePsdWithLast::Exec(QString msg)
{

}
