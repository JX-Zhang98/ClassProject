#include "mail.h"
#include "databs.h"

Mail::Mail()
{
//let us learn to bark like a cat, miao miao miao miao together~

}
Mail::Mail(int idd, QString snder, QString rcver,QString tim, QString ttl, QString cont )
{
    id = idd;
    sender = snder;
    receiver = rcver;
    title = ttl;
    content = cont;
    time = tim;
    isread=0;
    senderDelete=0;
    receiverDelete=0;
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
void Mail::setTitle(QString ttl)
{
    title = ttl;
}
void Mail::changeCont(QString txt)
{
    content = txt;
}
bool Mail::setIsread()
{
    isread = 1;        // has read
    /*
    QSqlQuery query;
    QString commond;
    query.prepare("updata mail set isread = 1 where id=:id");
    query.bindValue(":id",id);
    query.exec();*/
    Databs tmp;
    return tmp.isread(id);
}
bool Mail::setSenderDel()
{
    senderDelete=1;
    /*
    query.prepare("updata mail set senddelete = 1 where id =:id");
    query.bindValue(":id",id);
    query.exec();*/
    Databs tmp;
    return tmp.sendDelete(id, 0);
}
bool Mail::setReceiverDel()
{
    senderDelete=1;
    /*
    QSqlQuery query;
    query.prepare("updata mail set receivedelete = 1 where id =:id");
    query.bindValue(":id",id);
    query.exec();*/
    Databs tmp;
    return tmp.receiverDelete(id, 0);
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
bool Mail::getSenderDelete()
{
    return senderDelete;
}
bool Mail::getReceiverDelete()
{
    return receiverDelete;
}
