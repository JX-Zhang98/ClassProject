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
    /******all func about account is completed with argv as QString************/
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
    //get mails between name and victim
    QList<Mail> getMailBtwn(QString username, QString victim, int startWith, int num=15);
    //mark that the sender delete the mail   -> opera = 0 means delete while 1 means recover
    bool sendDelete(int id,int opera);
    //mark that the receiver delte teh mail  -> opera = 0 means delete while 1 means recover
    bool receiverDelete(int id,int opera);
    //mark that the mail has been read
    bool isread(int id);


    /************about relations*****************/
    // add victim into mail list, can set nickname, default is ""
    bool addIntoList(QString username, QString victim, QString nickname="");
    // delete victim from mail list
    bool delFromList(QString username, QString victim);
    // add victim into black list
    bool pullBlack(QString username, QString victim);
    // delete from black
    bool delFromBlack(QString username, QString victim);
    // check mails from black
    QList<Mail> getBlackMail(QString username, int startWith, int num=15);







private:
    QSqlDatabase db;
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
