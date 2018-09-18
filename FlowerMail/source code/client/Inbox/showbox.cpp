#include "showbox.h"
#include "ui_showbox.h"

ShowBox::ShowBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowBox)
{
    ui->setupUi(this);
}

ShowBox::~ShowBox()
{
    delete ui;
}

void ShowBox::showmail(Mail mail)
{
    ui->Sender->setText(u8"收件人："+mail.getSender());
    ui->Time->setText(u8"时间："+mail.getTime());
    ui->Title->setText(u8"主题："+mail.getTitle());
    ui->content->setHtml(mail.getCont());
}
