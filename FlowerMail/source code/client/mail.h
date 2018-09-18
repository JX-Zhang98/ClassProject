#ifndef MAIL_H
#define MAIL_H
#include <QDateTime>
class Mail
{
public:
    Mail();
    Mail(QString,QString,QString,QString,QString,bool,int);
    //have nothing to do with database, just to change value in class
    // set receiver, default to set sender, time is set in databs.h when send to database;
    // change the value of the class itself, don't need the return value;
    void setReceiver(QString rcver);
    void setSender(QString snder);
    void setId(int n);   //this should be completed in server,so ,,,you like is ok
    void setTitle(QString ttl);
    void changeCont(QString txt);
    void setTime();
    void setTime(QString);
    // the following operations need to be done both on client and database
    // bool value means whether the change on database is finished
    void setIsread(bool flag);
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

class MailInUI: public Mail
{
public:
    MailInUI(){beChecked=false;}
    MailInUI(Mail&mail);
    ~MailInUI(){}
    void setBeChecked(bool flag){beChecked=flag;}
    bool getBeChecked(){return beChecked;}
private:
    bool beChecked;
};

#endif // MAIL_H
