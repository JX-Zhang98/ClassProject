#ifndef MAIL_H
#define MAIL_H
#include <QDateTime>
//#include "databs.h"
class Mail
{
public:
    Mail();
    Mail(int idd, QString snder, QString rcver, QString ttl, QString cont, QString tim);

    //have nothing to do with database, just to change value in class
    // set receiver, default to set sender, time is set in databs.h when send to database;
    // change the value of the class itself, don't need the return value;
    void setReceiver(QString rcver);
    void setSender(QString snder);
    void setId(int n);   //this should be completed in server,so ,,,you like is ok
    void setTitle(QString ttl);
    void changeCont(QString txt);
    void setTime();
    // the following operations need to be done both on client and database
    // bool value means whether the change on database is finished
    bool setIsread();
    bool setSenderDel();
    bool setReceiverDel();

    int getId();
    QString getReceiver();
    QString getSender();
    QString getTitle();
    QString getCont();
    QString getTime();
    bool getIsRead();
    bool getSenderDelete();
    bool getReceiverDelete();
    //about attachment, nearly useless, ignore it
    //int getAttach()
    //other operations can be finished by call sendMail(Mail example) in databs.h

private:
    int id;
    QString sender;
    QString receiver;
    QString title;
    QString content;
    QString time;
    //int attach;

    bool isread;
    bool senderDelete;
    bool receiverDelete;

};

#endif // MAIL_H
