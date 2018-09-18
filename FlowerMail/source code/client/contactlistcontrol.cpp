#include "contactlistcontrol.h"

ContactlistControl::ContactlistControl()
{

}

void ContactlistControl::AddContact(QString addinfo)
{
    QString msg=QString("addcontact")+sep+UserInfoControl::user.GetUserName()+sep+addinfo;
    NetworkSocket::SendMsg(msg);
}
void ContactlistControl::ShowContact()
{
    QString msg=QString("showcontact")+sep+UserInfoControl::user.GetUserName();
    NetworkSocket::SendMsg(msg);
}
void ContactlistControl::ShowBlacklist()
{
    QString msg=QString("showblacklist")+sep+UserInfoControl::user.GetUserName();
    NetworkSocket::SendMsg(msg);
}
void ContactlistControl::AddBlacklist(QList<PublicInfo>list)
{
    QString msg=QString("addblacklist")+sep+UserInfoControl::user.GetUserName();
    foreach(PublicInfo info,list)
    {
        msg+=(sep+info.GetUserName());
    }
    NetworkSocket::SendMsg(msg);
}
void ContactlistControl::RestoreBlacklist(QList<PublicInfo>list)
{
    QString msg=QString("restoreblacklist")+sep+UserInfoControl::user.GetUserName();
    foreach(PublicInfo info,list)
    {
        msg+=(sep+info.GetUserName());
    }
    NetworkSocket::SendMsg(msg);
}
void ContactlistControl::DeleteContact(QList<PublicInfo>list)
{
    QString msg=QString("deletecontact")+sep+UserInfoControl::user.GetUserName();
    foreach(PublicInfo info,list)
    {
        msg+=(sep+info.GetUserName());
    }
    NetworkSocket::SendMsg(msg);
}
