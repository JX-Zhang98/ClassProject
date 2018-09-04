#include "mail.h"
#include "databs.h"

Mail::Mail()
{
//let us learn to bark like a cat, miao miao miao miao together~

}

// set receiver, default to set sender, time is set in databs.h when send to database;
void Mail::setReceiver(QString snder, QString rcver = NULL)
{
    sender = snder;
    receiver = rcver;
    //if receiver == null, means this is a draft
    return;
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
    QSqlQuery query;
    isread = 1;        // has read
    QString commond;
    query.prepare("updata mail set isread = 1 where id=:id");
    query.bindValue(":id",id);
    query.exec();

    return query.exec((const QString)commond);
}
bool Mail::setSenderDel()
{
    QSqlQuery query;
    senderDelete=1;
    query.prepare("updata mail set senddelete = 1 where id =:id");
    query.bindValue(":id",id);
    query.exec();
}
bool Mail::setReceiverDel()
{
    QSqlQuery query;
    senderDelete=1;
    query.prepare("updata mail set receivedelete = 1 where id =:id");
    query.bindValue(":id",id);
    query.exec();
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
