#include "mail.h"

Mail::Mail()
{
//let us learn to bark like a cat, miao miao miao miao together~

}
Mail::Mail(QString m_sender,QString m_receiver,QString m_title,QString m_content,QString m_time,bool m_isread,int m_id)
{
    sender=m_sender;
    receiver=m_receiver;
    title=m_title;
    content=m_content;
    time=m_time;
    isread=m_isread;
    id=m_id;
}
// set receiver, default to set sender, time is set in databs.h when send to database;
void Mail::setReceiver(QString rcver = NULL)
{
    //sender = snder;
    receiver = rcver;
    //if receiver == null, means this is a draft
    return;
}
void Mail::setSender(QString snder)
{
    sender = snder;
    return;
}
void Mail::setId(int n)
{
    id=n;
    return;
}
int Mail::getId()
{
    return id;
}
void Mail::setTime()
{
    QDateTime dt;
    QTime Time;
    QDate Date;
    dt.setTime(Time.currentTime());
    dt.setDate(Date.currentDate());
    time = dt.toString("yyyy:MM:dd:hh:mm");
    return ;
}
void Mail::setTime(QString mailTime)
{
    time=mailTime;
}
void Mail::setTitle(QString ttl)
{
    title = ttl;
}
void Mail::changeCont(QString txt)
{
    content = txt;
}
void Mail::setIsread(bool flag)
{
    isread=flag;
}
QString Mail::getReceiver()
{
    return receiver;
}
QString Mail::getSender()
{
    return sender;
}
QString Mail::getTitle()
{
    return title;
}
QString Mail::getCont()
{
    return content;
}
QString Mail::getTime()
{
    return time;
}
bool Mail::getIsRead()
{
    return isread;
}

 MailInUI::MailInUI(Mail&mail):Mail(mail)
{
     beChecked=false;
}
