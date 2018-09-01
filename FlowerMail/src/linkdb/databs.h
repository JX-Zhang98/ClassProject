#ifndef DATABS_H
#define DATABS_H
/*
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
    // register to add users
    bool addUser(QString username, QString password, QString  realname, QString telephone, int state);
    // check if the username exists when registing or logining in
    bool checkUserExist(QString username);
    //checks if the username and password match
    bool checkPass(QString username, QString password);
    //set question to protect the account, number range(1, 2, 3)
    bool setQuestion(int number, QString question, QString ans);
    //change information of user
    bool setInfo(QString columnn, QString info);
    //trans a string to md5
    QString md5(QString sou);
private:
    QSqlDatabase db;
    QSqlQuery query;
};
*/
#endif // DATABS_H
