#include "findpwdwindow.h"
#include "ui_findpwdwindow.h"
FindpwdWindow::FindpwdWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FindpwdWindow)
{

    ui->setupUi(this);
}

FindpwdWindow::~FindpwdWindow()
{

    delete ui;
}

void FindpwdWindow::on_Confirm_clicked()
{
    sec=new SecQuestion(this);
    this->hide();
    sec->show();
    sec->setusername(ui->Username->text());
}
