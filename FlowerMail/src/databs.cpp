#include "databs.h"

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
Databs::~Databs()
{
    db.close();
}

QString Databs::md5(QString sou)
{
    QString md5Psd;
    QByteArray ba,bb;
    QCryptographicHash md(QCryptographicHash::Md5);
    ba.append(sou);
    md.addData(ba);
    bb = md.result();
    md5Psd.append(bb.toHex());
    return md5Psd;
}

// register to add users
bool Databs::addUser(QString username, QString password, QString  realname, QString telephone)
{
    QSqlQuery query;
    QString md5Psd = md5(password+md5(password));
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
        return true;
    }
    else
    {
        qDebug() << "register fail!\nPlease retry.";
        return false;
    }

}

// check if the username exists when registing or logining in
bool Databs::checkUserExist(QString username)
{
    int flag=0;
    QSqlQuery query;
    QString commond = "select username from account where username='";
    commond += username;
    commond += "'";
    query.exec((const QString) commond);
    while(query.next())
    {
        flag=1;
     }
    qDebug() << username << (flag ==0);
    return flag==0;

}


//checks if the username and password match
bool Databs::checkPass(QString username, QString password)
{
    QSqlQuery query;
    QString commond = "select username from account where username='";
    commond += username;
    commond += "'";
    query.exec((const QString)commond);
    bool exist=0;
    while (query.next())
    {
        exist=1;
    }
    if (!exist)
    {
        qDebug() << "you haven't register!";
        return false;
    }
    commond = "select password from account where username='";
    commond += username + "'";
    query.exec((const QString)commond);
    password = md5(password+md5(password));
    qDebug() << "password" << password;
    QString record;
    while(query.next())
    {
        record = query.value(0).toString();
    }
    qDebug() << "record" << record;
    if(!record.compare(password))
    {
        qDebug() << "login success";
        return true;
    }
     qDebug() << "password not match";
    return false;
}

//reset the password
bool Databs::reSetPass(QString name, QString newPass)
{
    QSqlQuery query;
    QString commond;
    QString pass = md5(newPass+md5(newPass));
    commond = "updata account set password = '";
    commond += pass + "' ";
    commond += "where username='"+name+"'";
    return query.exec((const QString)commond);
}

//get the security question
QString Databs::getQuestion(QString name)
{
    QSqlQuery query;
    QString commond;
    commond = "select question1 from account where username='";
    commond += name+"'";
    query.exec((const QString)commond);
    while(query.next())
    {
        return query.value(0).toString();
    }
    return "error";
}

//check ans of question
bool Databs::checkAns(QString name, QString ans)
{
    QSqlQuery query;
    QString commond;
    commond = "select ans1 from account where username='";
    commond += name+"'";
    while(query.next())
    {
        if(ans.compare(query.value(0).toString()))
            return false;
        return true;
    }
    return false;
}

//set question to protect the account, number range(1, 2, 3)
bool Databs::setQuestion(QString question, QString ans, QString name)
{
    QSqlQuery query;
    QString commond;
    commond = "updata account set question1 = '";
    commond += question+"' ";
    commond += "where username='"+name+"'";
    bool step1 = query.exec((const QString)commond);
    commond = "updata account set ans1 = '";
    commond += ans+"' ";
    commond += "where username='"+name+"'";
    bool step2 = query.exec((const QString)commond);
    return (step1&&step2);
}


//change information of user
//bool Databs::setInfo(QString columnn, QString info){}


