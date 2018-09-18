#include "changepwdwindow.h"
#include "ui_Changepwdwindow.h"
ChangepwdWindow::ChangepwdWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChangepwdWindow)
{
    ui->setupUi(this);
}

ChangepwdWindow::~ChangepwdWindow()
{
    delete ui;
}
void ChangepwdWindow::on_ok_clicked()
{
    if(ui->Nowpwd->text()!=ui->Nowpwdagain->text())
    {
        ui->nowpassagain->setText("两次输入不一致");
        //ui->Lastpwd->setText("");
        ui->Nowpwd->setText("");
        ui->Nowpwdagain->setText("");
        return;
    }
    UserInfoControl::ChangePsd(ui->Nowpwd->text());
    QMessageBox::about(NULL, "", u8"密码修改成功！");
    this->hide();
}
