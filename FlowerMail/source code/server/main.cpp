#include "mainwindow.h"
#include <QApplication>
# include "databs.h"
#include "mail.h"
#include "serverwidget.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Databs v;
    //v.addUser("test", "123456");
    ServerWidget w;
    w.show();
    /*Databs v;
    qDebug() << "add user JX_Zhang" << v.addUser("JX_Zhang", "123456");
    qDebug()<< "check exist1" << v.checkUserExist("JX_Zhang");
    qDebug()<< "check exist0" << v.checkUserExist("Zhangjiaxi");
    qDebug()<< "checkpass true " << v.checkPass("JX_Zhang", "123456");
    qDebug()<< "checkpass false" << v.checkPass("JX_Zhang", "654321");
    qDebug()<< "set question" << v.setQuestion("whats your name?", "zjx","JX_Zhang");
    qDebug()<< "set info" << v.setInfo("张嘉熙", "110","JX_Zhang");
    qDebug()<< "reset password" << v.reSetPass("JX_Zhang", "654321");
    qDebug()<< "get question" << v.getQuestion("JX_Zhang");
    qDebug()<< "check ans1" << v.checkAns("JX_Zhang", "zjx");
    qDebug()<< "check ans0" << v.checkAns("JX_Zhang", "sdf");
    qDebug()<< "your real name" << v.getRealName("JX_Zhang");
    qDebug()<< "your phone" << v.getTelephone("JX_Zhang");*/

    /****************relation*******************/
    //v.addUser("zjx", "123456");
    //qDebug()<<v.addIntoList("JX_Zhang", "zjx", "sameperson");
    //qDebug()<<v.addIntoList("JX_Zhang", "zjx");
    //qDebug()<<v.delFromList("JX_Zhang", "zjx");
    //qDebug()<<v.pullBlack("JX_Zhang", "zjx");
    //qDebug()<<v.delFromBlack("JX_Zhang", "zjx");








    //Mail m(5, "zjx", "tmp", "20158684654654", "test contne!", "testC0nt3nt!@#硕神硕神，你怎么这么强啊!!!!!！");
    //qDebug() << "send mail" << v.sendMail(m);
    //qDebug()<< "save draft" << v.saveDraft(m);
    //qDebug() << "send"

    //v.receiveMail("tmp", 0);
    return a.exec();
}
