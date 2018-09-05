#include "databs.h"

Databs::Databs()
{
    db=QSqlDatabase::addDatabase("QMYSQL");
    while (!db.open())
    {
        db.setHostName("localhost");
        db.setUserName("flower");
        db.setPassword("123456");
        db.setDatabaseName("flowermail");
    }
    qDebug()<<"open success";
}
Databs::~Databs()
{
    db.close();
}


/**************************************************************************************/
/**************************Below are account related functions*************************/
/**************************************************************************************/
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
bool Databs::addUser(QString username, QString password)
{
    QSqlQuery query;
    QString md5Psd = md5(password+md5(password));
    QString commond;
    commond = "insert into account (username, password) values ('";
    commond += username;
    commond += "', '";
    commond += md5Psd;
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
    return flag;

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

//change information of user, this is done in setting , including realname, telephone
bool setInfo(QString realname, QString tele, QString name)
{
    QSqlQuery query;
    QString commond;
    bool step1, step2;
    commond = "updata account set realname = '";
    commond += realname + "' ";
    commond += "where username='" + name + "'";
    step1 = query.exec(commond);
    commond = "updata account set telephone = '";
    commond += tele + "' ";
    commond += "where username='" + name + "'";
    step2 = query.exec(commond);
    return (step1&&step2);
}

//get name and tele
QString getRealName(QString username)
{
    QSqlQuery query;
    QString commond;
    commond = "select realname from account where username ='";
    commond += username + "'";
    query.exec(commond);
    query.next();
    return query.value(0).toString();
}
QString getTelephone(QString username)
{
    QSqlQuery query;
    QString commond;
    commond = "select telephone from account where username ='";
    commond += username + "'";
    query.exec(commond);
    query.next();
    return query.value(0).toString();
}

/**************************************************************************************/
/**************************Below are mail related functions****************************/
/**************************************************************************************/

//send the mail to database
//id start from 1, there is no record whitch id=1
bool Databs::sendMail(Mail mail)
{
    QSqlQuery query;
    query.exec("select count(*) from mail");
    query.next();
    int id = query.value(0).toInt()+1;
    QString sender = mail.getSender();
    QString receiver = mail.getReceiver();
    QString time = mail.getTime();
    QString title = mail.getTitle();
    QString content = mail.getCont();
    //int read = mail.getIsRead();
    //int sendDeleted = mail.getSenderDelete();
    //int receiverDeleted = mail.getReceiverDelete();
    QString commond;
    commond = "insert into mail (id, sender, receiver, time, title, content, ";
    commond += "attach, isread, senddelete, receivedelete) values";
    commond += "(:id, :sender, :receiver, :time, :title, :content, ";
    commond += "0, 0, 0, 0)";
    query.prepare((const QString)commond);
    query.bindValue(":id", id);
    query.bindValue(":sender", sender);
    query.bindValue(":receiver", receiver);
    query.bindValue(":time", time);
    query.bindValue(":title", title);
    query.bindValue(":content", content);
    return query.exec();
}

//save the mail as draft, with receiver is null
bool Databs::saveDraft(Mail mail)
{
    QSqlQuery query;
    query.exec("select count(*) from mail");
    query.next();
    int id = query.value(0).toInt()+1;
    qDebug()<<id;
    QString sender = mail.getSender();
    QString receiver = "";
    QString time = mail.getTime();
    QString title = mail.getTitle();
    QString content = mail.getCont();
    QString commond;
    commond = "insert into mail (id, sender, receiver, time, title, content, ";
    commond += "attach, isread, senddelete, receivedelete) values";
    commond += "(:id, :sender, :receiver, :time, :title, :content, ";
    commond += "0, 0, 0, 0)";
    query.prepare((const QString)commond);
    query.bindValue(":id", id);
    query.bindValue(":sender", sender);
    query.bindValue(":receiver", receiver);
    query.bindValue(":time", time);
    query.bindValue(":title", title);
    query.bindValue(":content", content);
    qDebug()<<query.exec();
    return query.exec();
}

//get the mails whitch sended to me, and save it in a list,receive 15 per time
QList<Mail> Databs::receiveMail(QString username, int startWith, int num)
{
    int count=0;
    QSqlQuery query;
    QList<Mail> retval;
    query.prepare("select * from mail where receiver = :receiver");
    query.bindValue(":receiver", username);
    query.exec();
    while(query.next())
    {
        if(startWith)
        {
            startWith--;
            continue;
        }
        if(++count>num)
            break;
        int id=query.value(0).toInt();
        QString sender = query.value(1).toString();
        QString receiver = query.value(2).toString();
        QString time = query.value(3).toString();
        QString title = query.value(4).toString();
        QString content = query.value(5).toString();
        //qDebug() << "sender->" << sender;
        //qDebug() << "content>" << content;
        Mail tmp(id, sender, receiver, time, title, content);
        retval.append(tmp);
    }
    return retval;
}
//get the sended mails, 15 per time, jump $startWith mails before return
QList <Mail> Databs::getSended(QString username, int startWith, int num)
{
    QSqlQuery query;
    int count=0;
    QList<Mail> retval;
    query.prepare("select * from mail where sender = :sender where receiver !=''");
    query.bindValue(":sender", username);
    query.exec();
    while(query.next())
    {
        if(startWith)
        {
            startWith--;
            continue;
        }
        if(++count>num)
            break;
        int id=query.value(0).toInt();
        QString sender = query.value(1).toString();
        QString receiver = query.value(2).toString();
        QString time = query.value(3).toString();
        QString title = query.value(4).toString();
        QString content = query.value(5).toString();
        Mail tmp(id, sender, receiver, time, title, content);
        retval.append(tmp);
    }
    return retval;
}
QList <Mail> getDraft(QString username, int startWith, int num)      //receiver null
{
    QSqlQuery query;
    int count=0;
    QList<Mail> retval;
    query.prepare("select * from mail where sender = :sender where receiver =''");
    query.bindValue(":sender", username);
    query.exec();
    while(query.next())
    {
        if(startWith)
        {
            startWith--;
            continue;
        }
        if(++count>num)
            break;
        int id=query.value(0).toInt();
        QString sender = query.value(1).toString();
        QString receiver = query.value(2).toString();
        QString time = query.value(3).toString();
        QString title = query.value(4).toString();
        QString content = query.value(5).toString();
        Mail tmp(id, sender, receiver, time, title, content);
        retval.append(tmp);
    }
    return retval;
}
//get all mails deleted, receiver=me&&recverdeleted || sender=me&&senderdeleted
QList<Mail> Databs::getDeleted(QString username, int startWith, int num)
{
    QSqlQuery query;
    int count=0;
    QList<Mail> retval;
    query.prepare("select * from mail where (sender = :sender and senddelete = 1) or (receiver = :receiver and receivedelete = 1)");
    query.bindValue(":sender", username);
    query.bindValue(":receiver", username);
    query.exec();
    while(query.next())
    {
        if(startWith)
        {
            startWith--;
            continue;
        }
        if(++count>num)
            break;
        int id=query.value(0).toInt();
        QString sender = query.value(1).toString();
        QString receiver = query.value(2).toString();
        QString time = query.value(3).toString();
        QString title = query.value(4).toString();
        QString content = query.value(5).toString();
        Mail tmp(id, sender, receiver, time, title, content);
        retval.append(tmp);
    }
    return retval;
}

//mark that the sender delete the mail
bool Databs::sendDelete(int id)
{
    QSqlQuery query;
    query.prepare("updata mail set senddelete = 1 where id = :id");
    query.bindValue(":id", id);
    return query.exec();
}
//mark that the receiver delte teh mail
bool Databs::receiverDelete(int id)
{
    QSqlQuery query;
    query.prepare("updata mail set receivedelete = 1 where id = :id");
    query.bindValue(":id", id);
    return query.exec();
}
//mark that the mail has been read
bool Databs::isread(int id)
{
    QSqlQuery query;
    query.prepare("updata mail set isread = 1 where id = :id");
    query.bindValue(":id", id);
    return query.exec();
}





























