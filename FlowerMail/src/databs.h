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
class Databs
{
public:
    Databs();
    ~Databs();
    // register to add users
    bool addUser(QString username, QString password, QString  realname, QString telephone);
    // check if the username exists when registing or logining in
    bool checkUserExist(QString username);
    //checks if the username and password match
    bool checkPass(QString username, QString password);
    //set question to protect the account, number range(1, 2, 3)
    bool setQuestion(QString question, QString ans, QString name);
    //change information of user, this is done in setting , password included
    //bool setInfo(QString columnn, QString info);
    //trans a string to md5
    QString md5(QString sou);
    //reset pass
    bool reSetPass(QString name, QString newPass);
    //get the security question
    QString getQuestion(QString name);
    //check ans of question
    bool checkAns(QString name, QString ans);
private:
    QSqlDatabase db;
    //QSqlQuery query;
};

#endif // DATABS_H
