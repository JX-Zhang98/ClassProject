#include "secquestion.h"
#include "ui_secquestion.h"

SecQuestion::SecQuestion(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SecQuestion)
{
    ui->setupUi(this);
    UserInfoControl::GetSecureQuestion(username);

}

SecQuestion::~SecQuestion()
{
    delete ui;
}

void SecQuestion::on_OK_clicked()
{
    UserInfoControl::CheckSecureQuestion(username,ui->answer->text());
}
void SecQuestion::Exec1(QString msg)
{
    ui->question->setText(msg);
}
void SecQuestion::Exec2(QString msg)
{
    if(msg=="success")
    {
        QMessageBox::about(NULL, "", u8"密保问题验证成功！");
        this->hide();
        change->show();
    }
    else
    {
        QMessageBox::about(NULL, "", u8"密保问题验证失败");
        this->hide();
    }
}

