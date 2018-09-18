#include "adduser.h"
#include "ui_adduser.h"
addUser::addUser(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addUser)
{
    ui->setupUi(this);
     ui->pwdin->setEchoMode(QLineEdit::Password);
     ui->pwdinagain->setEchoMode(QLineEdit::Password);
}

addUser::~addUser()
{
    delete ui;
}
void addUser::Exec(QString msg)
{
    if(msg=="success")
    {
        this->hide();
        QMessageBox::about(NULL, "", u8"注册成功！");
    }
    else
    {
        this->hide();
        QMessageBox::about(NULL, "", u8"用户名已被使用");
    }
}
void addUser::on_ok_in_clicked()
{
    if(ui->pwdin->text()!=ui->pwdinagain->text())
    {
        ui->pwdagain->setText(u8"两次输入密码不一致");
        return;
    }
    UserInfoControl::Register(ui->username->text(),ui->pwdin->text());
}
