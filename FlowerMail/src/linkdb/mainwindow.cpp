#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    linkDatabase();
    delete ui;
}

void MainWindow::linkDatabase()
{
    db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setUserName("flower");
    db.setPassword("123456");
    db.setDatabaseName("testmail");
    bool ok=db.open();
    if(ok)
    {
        qDebug()<<"open success";
        qDebug()<<db.driverName();

        QSqlQuery query;
        //qDebug()<< query.exec("SELECT realname FROM account");

        //list the content of columns
        query.exec("SELECT realname FROM account");
        while (query.next())
        {
            QString country = query.value(0).toString();
            qDebug()<<country;

        }



        //insert data
        qDebug()<< query.exec("insert into account (username, password, realname, telephone, state) values ('咸鱼', '654321', 'ZJX', '119', 1)");
        //show tables
        query.exec("show tables");
        query.exec("select username from account");
        while (query.next())
        {
            QString country = query.value(0).toString();
            qDebug()<<country;

        }


        //update data
        qDebug()<< query.exec("update account set realname = '允许空' where username = 'saltyfish'");

        //delete
        qDebug() << query.exec("delete from account where realname = '允许空'");




    }
    else
    {
        qDebug()<<"open error because"<<this->db.lastError();
    }
}
