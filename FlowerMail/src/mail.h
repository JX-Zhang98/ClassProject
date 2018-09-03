#ifndef MAIL_H
#define MAIL_H
#include "databs.h"

class Mail
{
public:
    Mail();
    //have nothing to do with database, just to change value in class
    // set receiver, default to set sender
    bool setReceiver(QString sender, QString receiver = NULL);
    bool setTitle(QString title);
    bool changeCont(QString text);
    QString getReceiver();
    QString getSender();
    QString getCont();
    //other operations can be finished by call sendMail(Mail example) in databs.h
private:
    QString sender;
    QString receiver;
    QString title;
    QString content;
};

#endif // MAIL_H
