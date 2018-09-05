#ifndef DATABS_H
#define DATABS_H

#include <QtSql/QSqlDatabase>
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlDriver>
#include <QCryptographicHash>
#include <QByteArray>
#include "mail.h"
#include <QList>
class Databs
{
public:
    Databs();
    ~Databs();
    /**********account*********************/
    // register to add users
    bool addUser(QString username, QString password);
    // check if the username exists when registing or logining in
    //exits return 1, not exist return 0
    bool checkUserExist(QString username);
    //checks if the username and password match
    bool checkPass(QString username, QString password);
    //set question to protect the account, number range(1, 2, 3)
    bool setQuestion(QString question, QString ans, QString name);
    //change information of user, this is done in setting , including realname, telephone
    bool setInfo(QString realname, QString tele, QString name);
    //trans a string to md5
    QString md5(QString sou);
    //reset pass
    bool reSetPass(QString name, QString newPass);
    //get the security question
    QString getQuestion(QString name);
    //check ans of question
    bool checkAns(QString name, QString ans);
    //get name and tele
    QString getRealName(QString username);
    QString getTelephone(QString username);


    /***************mail******************/
    //send the mail to database
    bool sendMail(Mail mail);
    //save the mail as draft, with receiver is null
    bool saveDraft(Mail mail);
    //get the mails whitch sended to me, and save it in a list,receive 15 per time
    QList<Mail> receiveMail(QString username, int startWith, int num=15);
    //get the sended mails, 15 per time, jump $startWith mails before return
    //startWith means how many mails would be passed before get to client from server, for example ,startWith=0,15,30...
    QList <Mail> getSended(QString username, int startWith, int num=15);      //receiver not null
    QList <Mail> getDraft(QString username, int startWith, int num=15);       //receiver null
    //get all mails deleted, receiver=me&&recverdeleted || sender=me&&senderdeleted
    QList<Mail> getDeleted(QString username, int startWith, int num=15);
    //mark that the sender delete the mail
    bool sendDelete(int id);
    //mark that the receiver delte teh mail
    bool receiverDelete(int id);
    //mark that the mail has been read
    bool isread(int id);





private:
    QSqlDatabase db;
    //QSqlQuery query;
};

#endif // DATABS_H




/******************************
#include <QtSql/QSqlDatabase>
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlDriver>
#include <QCryptographicHash>
#include <QByteArray>


QSqlDatabase db;
    db=QSqlDatabase::addDatabase("QMYSQL");
    while (!db.open())
    {
        db.setHostName("192.168.43.112");
        db.setPort(3306);
        db.setUserName("flower");
        db.setPassword("123456");
        db.setDatabaseName("mail");
    }
    qDebug()<<"open success";

*/
