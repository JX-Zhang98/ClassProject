#include "mailcontrol.h"

MailControl::MailControl()
{

}
int MailControl::getMailNum()
{
    int cnt=NetworkSocket::ReadMsg().toInt();
    return cnt;
}
QStringList MailControl::MailSplit(QString msg)
{
    return msg.split(spm);
}
QList<Mail> MailControl::getMail(int mailnum)
{
    QList<Mail> maillist;
    for(int i=0;i<mailnum;i++)
    {
        QStringList mailinfo=MailSplit(NetworkSocket::ReadMsg());
        Mail temp;
        temp.setSender(mailinfo[0]);
        temp.setReceiver(mailinfo[1]);
        temp.setTime(mailinfo[2]);
        temp.setTitle(mailinfo[3]);
        temp.changeCont(mailinfo[4]);
        maillist.append(temp);
    }
    return maillist;
}
//发邮件
void MailControl::SendMail(QList<Mail> mail)
{
    QString msg=QString("sendmail")+sep;
    foreach(Mail m,mail)
    {
        msg+=m.getSender()+spm+m.getReceiver()
                    +spm+m.getTitle()+spm+m.getCont();

        msg+=sep;
    }
    qDebug()<<msg;
    NetworkSocket::SendMsg(msg);

}
//保存草稿
void MailControl::SaveDraft(Mail m)
{
    QString msg=QString("savedraft")+sep;
    msg+=m.getSender()+spm+m.getReceiver()
                +spm+m.getTitle()+spm+m.getCont();

    msg+=sep;
    qDebug()<<msg;
    NetworkSocket::SendMsg(msg);

}

//收邮件
void MailControl::ReceiveMail(int state)
{
    switch(state)
    {
    case 1:
    {
        QString msg=QString("receive")+sep+UserInfoControl::user.GetUserName();
        NetworkSocket::SendMsg(msg);
        return;
    }
    case 2:
    {
        QString msg=QString("receivedrafting")+sep+UserInfoControl::user.GetUserName();
        NetworkSocket::SendMsg(msg);
        return;
    }
    case 3:
    {
        QString msg=QString("receivesending")+sep+UserInfoControl::user.GetUserName();
        NetworkSocket::SendMsg(msg);
        return;
    }
    case 4:
    {
        QString msg=QString("receivedeleting")+sep+UserInfoControl::user.GetUserName();
        NetworkSocket::SendMsg(msg);
        return;
    }
    }
}
void MailControl::DeleteMail(QList<Mail> mail)
{
    QString msg=QString("deletemail")+sep;
    foreach(Mail m,mail)
    {
        msg+=QString::number(m.getId());
        msg+=sep;
    }
    NetworkSocket::SendMsg(msg);
}
void MailControl::DeleteSendingMail(QList<Mail> mail)
{
    QString msg=QString("deletesendingmail")+sep;
    foreach(Mail m,mail)
    {
        msg+=QString::number(m.getId());
        msg+=sep;
    }
    NetworkSocket::SendMsg(msg);
}
void MailControl::UndeleteMail(QList<Mail> mail)
{
    QString msg=QString("undeletemail")+sep+UserInfoControl::user.GetUserName()+sep;
    foreach(Mail m,mail)
    {
        msg+=QString::number(m.getId());
        msg+=sep;
    }
    NetworkSocket::SendMsg(msg);
}
void MailControl::CompleteDeleteMail(QList<Mail> mail)
{
    QString msg=QString("completedeletemail")+sep;
    foreach(Mail m,mail)
    {
        msg+=QString::number(m.getId());
        msg+=sep;
    }
    NetworkSocket::SendMsg(msg);
}
void MailControl::IsReadMail(QList<Mail> mail)
{
    QString msg=QString("setisreadmail")+sep;
    foreach(Mail m,mail)
    {
        msg+=QString::number(m.getId());
        msg+=sep;
    }
    NetworkSocket::SendMsg(msg);

}
void MailControl::SetAutoReplay(QString content)
{
    QString msg=QString("setautoreply")+sep+UserInfoControl::user.GetUserName()+sep+content;
    NetworkSocket::SendMsg(msg);
}



