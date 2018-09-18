#include "loginwidget.h"
#include "ui_loginwidget.h"

LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
        //ui->pwd->setEchoMode(QLineEdit::Password);

    }

    LoginWidget::~LoginWidget()
    {
        delete ui;

    }


    void LoginWidget::Exec(QString msg)
    {
        if(msg=="success")
        {
            UserInfoControl::user.SetUserName(ui->namelineEdit->text());
            QMessageBox::about(NULL, "", u8"登陆成功！");
            emit sendtocontrol();
        }
        else
        {
            QMessageBox::about(NULL, "", u8"用户名和密码不匹配！");
            ui->namelineEdit->setText("");
            ui->psdlineEdit->setText("");
        }
    }


void LoginWidget::on_loginButton_clicked()
{
    QString username=ui->namelineEdit->text();
    QString psd=ui->psdlineEdit->text();
    UserInfoControl::Login(username,psd);
}

void LoginWidget::on_registerButton_clicked()
{
    regis=new addUser();
    regis->show();
}

void LoginWidget::on_findpsdButton_clicked()
{
    findpsd=new FindpwdWindow();
    findpsd->show();
}
