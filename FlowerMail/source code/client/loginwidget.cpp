#include "loginwidget.h"
#include "ui_loginwidget.h"

LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
    mailw=new MailWidget;


    connect(NetworkSocket::GetTcpSocket(),&QTcpSocket::connected,
            [=]()
            {
                qDebug()<<u8"成功连接";
            }
            );
}

LoginWidget::~LoginWidget()
{
    delete ui;
}



void LoginWidget::on_ConnectButton_clicked()
{
    UserInfo nowuser(ui->UserNameLineEdit->text(),"","",ui->PsdLineEdit->text(),"","");
    UserInfoControl::Login(nowuser);
}
