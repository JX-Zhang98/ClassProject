#include "controlapp.h"
#include "loginwidget.h"
ControlApp::ControlApp()
{
    //lineEdit->setEchoMode(QLineEdit::PasswordEchoOnEdit);//
    loginw=new LoginWidget();
    loginw->show();
    //mailw=new MailWidget();
    //mailw->show();
    connect(loginw,&LoginWidget::sendtocontrol,this,&ControlApp::toMailWidget);

    connect(NetworkSocket::GetTcpSocket(),&QTcpSocket::readyRead,
            [=]()
    {
        QString array=NetworkSocket::ReadMsg();
        qDebug()<<array;
        QStringList list=array.split("!@");
        qDebug()<<list;
        if(list.at(0)=="login")
        {
            loginw->Exec(list.at(1));
        }
        else if(list.at(0)=="register")
        {
            loginw->regis->Exec(list.at(1));
        }
        else if(list.at(0)=="getquestion")
        {
            loginw->findpsd->sec->Exec1(list.at(1));
        }
        else if(list.at(0)=="checkanswer")
        {
            loginw->findpsd->sec->Exec2(list.at(1));
        }
        else if(list.at(0)=="changepsdwithlast")
        {

        }
        else if(list.at(0)=="getalluserinfo")
        {
            qDebug()<<list;
            UserInfoControl::user.GetUserName()=list.at(1);
            UserInfoControl::user.GetPhoneNumber()=list.at(2);
            UserInfoControl::user.GetRealName()=list.at(3);
            UserInfoControl::user.GetPassword()=list.at(4);
            UserInfoControl::user.GetSecureQuestion()=list.at(5);
            UserInfoControl::user.GetSecureAnswer()=list.at(6);
        }
        else if(list.at(0)=="receive")
        {
            qDebug()<<"re";
            mailw->inbox->Exec(list);
        }
        else if(list.at(0)=="receivedrafting")
        {
            qDebug()<<"draft";
            mailw->draftBox->Exec(list);
        }
        else if(list.at(0)=="receivesending")
        {
             qDebug()<<"send";
            mailw->sendBox->Exec(list);
        }
        else if(list.at(0)=="receivedeleting")
        {
             qDebug()<<"del";
            mailw->deleteBox->Exec(list);
        }
        else if(list.at(0)=="showcontact")
        {
            mailw->contractBox->Exec(list);
        }
        else if(list.at(0)=="showblacklist")
        {
            mailw->blacklist->Exec(list);
        }
    }
    );
}
void ControlApp::toMailWidget()
{
    mailw=new MailWidget();
    mailw->show();
    loginw->hide();
}
