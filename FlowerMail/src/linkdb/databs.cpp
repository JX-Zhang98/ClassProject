/*#include "databs.h"

Databs::Databs()
{
    db=QSqlDatabase::addDatabase("QMYSQL");
    while (!db.open())
    {
        db.setHostName("localhost");
        db.setUserName("flower");
        db.setPassword("123456");
        db.setDatabaseName("testmail");
    }
    qDebug()<<"open success";

}
QString md5(QString sou)
{
    QString ans;
    QByteArray bb;
    //bb = QCryptographicHash::hash ( sou.toAscii(), QCryptographicHash::Md5 );
    ans.append(bb.toHex());
    return ans;
}

// register to add users
bool Databs::addUser(QString username, QString password, QString  realname, QString telephone, int state)
{
    QString md5Psd = md5(password);
    QString commond;
    commond = "insert into account (username, password, realname, telephone, state) values ('";
    commond += username;
    commond += "', '";
    commond += md5Psd;
    commond += "', '";
    commond += realname;
    commond += "', '";
    commond += telephone;
    commond += "', 1)";
    //qDebug()<< query.exec("insert into account (username, password, realname, telephone, state) values ('saltyFish', '654321', 'ZJX', '119', 1)");
    if (query.exec((const QString)commond))
    {
        qDebug() << "register success!";
    }
    else
    {
        qDebug() << "register fail!\nPlease retry.";
    }

}


// check if the username exists when registing or logining in
bool Databs::checkUserExist(QString username)
{

}


//checks if the username and password match
bool Databs::checkPass(QString username, QString password)
{

}


//set question to protect the account, number range(1, 2, 3)
bool Databs::setQuestion(int number, QString question, QString ans)
{

}


//change information of user
bool Databs::setInfo(QString columnn, QString info)
{

}
*/
