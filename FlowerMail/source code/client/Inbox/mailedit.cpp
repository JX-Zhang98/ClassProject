#include "mailedit.h"
#include "ui_mailedit.h"
#include <QDebug>

MailEdit::MailEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MailEdit)
{
    ui->setupUi(this);
    //username=UserInfoControl::user.GetUserName();
}

MailEdit::~MailEdit()
{
    delete ui;
}

void MailEdit::EditMail(Mail mail)
{
    ui->receiverEdit->setText(mail.getReceiver());
    ui->titleEdit->setText(mail.getTitle());
    ui->richTextEdit->SetContent(mail.getCont());
}

void MailEdit::EditMail(QList<PublicInfo> recelist)
{
    Clear();
    foreach(PublicInfo rece,recelist)
    {
        //qDebug()<<rece.GetUserName()<<"1";
        ui->receiverEdit->moveCursor(QTextCursor::End);
        ui->receiverEdit->insertPlainText(rece.GetUserName()+";");
    }
}

void MailEdit::Clear()
{
    ui->receiverEdit->clear();
    ui->titleEdit->clear();
    ui->richTextEdit->clear();
}

void MailEdit::on_sendMailButton_clicked()
{
    QList<Mail> maillist;
    Mail temp;
    if(ui->receiverEdit->toPlainText()==QString(""))
    {
        QMessageBox::critical(nullptr,u8"错误",u8"请输入收件人");
    }
    QStringList receiverList=ui->receiverEdit->toPlainText().split(";");
    QString title=ui->titleEdit->text();
    QString content=ui->richTextEdit->ContentInHtml();

    temp.setSender(UserInfoControl::user.GetUserName());
    temp.setTitle(title);
    temp.changeCont(content);
    temp.setTime();
    temp.setIsread(false);
    foreach(QString receiver,receiverList)
    {
        if(receiver!="")
        {
            temp.setReceiver(receiver);
            maillist.append(temp);
        }
    }
    //qDebug()<<maillist.length();
    Clear();
    qDebug()<<"sendmail";
    MailControl::SendMail(maillist);
}

void MailEdit::on_draftButton_clicked()
{
    Mail temp;
    QString receiver=ui->receiverEdit->toPlainText();
    QString title=ui->titleEdit->text();
    QString content=ui->richTextEdit->ContentInHtml();
    temp.setSender(UserInfoControl::user.GetUserName());
    temp.setReceiver(receiver);
    temp.setTitle(title);
    temp.changeCont(content);
    temp.setTime();
    temp.setIsread(false);

    Clear();
    qDebug()<<"savedraft";
    MailControl::SaveDraft(temp);
}
