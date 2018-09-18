#include "userinfocontrol.h"
UserInfo UserInfoControl::user("","","","","","");
UserInfoControl::UserInfoControl()
{
    UserInfo user("","","","","","");
}
QStringList UserInfoControl::UserInfoSplit(QString str)
{
    return str.split(sep);
}

void UserInfoControl::Register(QString name,QString psd)
{
    QString msg=QString("register")+sep+name+sep+psd;
    NetworkSocket::SendMsg(msg);
}

void UserInfoControl::Login(QString name,QString psd)
{
    QString msg=QString("login")+sep+name+sep+psd;
    NetworkSocket::SendMsg(msg);
}
void UserInfoControl::CheckSecureQuestion(QString name,QString ans)
{
    QString msg=QString("checkanswer")+sep+name+sep+ans;
    NetworkSocket::SendMsg(msg);

}
void UserInfoControl::GetSecureQuestion(QString name)
{
    QString msg=QString("getquestion")+sep+name;
    NetworkSocket::SendMsg(msg);
    return;
}
void UserInfoControl::GetAllInfo(QString name)
{
    QString msg=QString("getalluserinfo")+sep+name;
    NetworkSocket::SendMsg(msg);
    return;
}
void UserInfoControl::ChangePsd(QString lastpsd,QString newpsd)
{
    QString msg=QString("changepsdwithlast")+sep+user.GetUserName()+sep+lastpsd+sep+newpsd;
    NetworkSocket::SendMsg(msg);
    return;
}
void UserInfoControl::ChangePsd(QString newpsd)
{
    QString msg=QString("changepsd")+sep+user.GetUserName()+sep+newpsd;
    NetworkSocket::SendMsg(msg);
    return ;
}
