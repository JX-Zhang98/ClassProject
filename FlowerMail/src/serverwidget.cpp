#include "serverwidget.h"
#include "ui_serverwidget.h"
#include "databs.h"
#define sep "!@"
#define spm "@#"

ServerWidget::ServerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerWidget)
{
    ui->setupUi(this);

    tcpServer=nullptr;
    tcpSocket=nullptr;
    //指定父对象，可以让他自动回收内存
    tcpServer=new QTcpServer(this);
    //tcpSocket=new QTcpSocket(this);
    tcpServer->listen(QHostAddress::Any,8888);

    setWindowTitle(u8"服务器：8888");

    connect(tcpServer,&QTcpServer::newConnection,
            [=]()
            {
                //取出建立好连接的套接字,给tcpSocket指针分配内存？
                tcpSocket=tcpServer->nextPendingConnection();

                //获取对方ip和端口
                QString ip=tcpSocket->peerAddress().toString();
                quint16 port=tcpSocket->peerPort();
                QString temp=QString(u8"[%1:%2]:成功连接").arg(ip).arg(port);
                ui->textEditRead->setText(temp);

                connect(tcpSocket,&QTcpSocket::readyRead,
                        [=]()
                        {
                            //从通信套接字取内容
                            QString array=tcpSocket->readAll();
                            analysis(array);
                            //解析字符串，验证数据库是否成功
                            /*QStringList usrpsd = array.split("!@");
                            //qDebug() << usrpsd[0];
                            //qDebug() << usrpsd[1];
                            QString opera = usrpsd[0];
                            QString username = usrpsd[1];
                            QString password = usrpsd[2];
                            ui->textEditRead->append(username);
                            ui->textEditRead->append(password);
                            Databs db;
                            if(db.checkPass(username, password))
                            {
                                QString str="login!@success";
                                //socket通信建立好后，不用再考虑对方ip，直接用socket套接字发就可以
                                tcpSocket->write(str.toUtf8().data());
                            }*/


                }
                );
            }
            );

}

ServerWidget::~ServerWidget()
{
    delete ui;
}

void ServerWidget::on_SendButton_clicked()
{
    if(tcpSocket==nullptr)
    {
        //qDebug()<<"11";
        //QMessageBox message(QMessageBox::Warning,"Information","Connection Error",QMessageBox::Yes|QMessageBox::No);
        return;
    }
    //获取编辑区内容
    QString str=ui->textEditWrite->toPlainText();
    //socket通信建立好后，不用再考虑对方ip，直接用socket套接字发就可以
    tcpSocket->write(str.toUtf8().data());
}

void ServerWidget::on_CloseButton_clicked()
{
    if(tcpSocket==nullptr)
    {
        //qDebug()<<"22";
        //QMessageBox message(QMessageBox::Warning,"Information","Connection Error",QMessageBox::Yes);
        return;
    }
    //主动和客户端断开连接
    tcpSocket->disconnectFromHost();
    tcpSocket->close();
    tcpSocket=nullptr;
}

void ServerWidget::analysis(QString order)
{
    ui->textEditRead->append(order);
    //解析字符串，验证数据库是否成功
    QStringList usrpsd = order.split("!@");
    Databs db;
    if(usrpsd.at(0)=="login")
    {
        QString str;
        if(db.checkPass(usrpsd.at(1), usrpsd.at(2)))
        {
            str="login!@success";
            //socket通信建立好后，不用再考虑对方ip，直接用socket套接字发就可
        }
        else str="login!@fail";
        tcpSocket->write(str.toUtf8().data());
    }
    else if(usrpsd.at(0)=="register")
    {
        QString str="register!@";
        if(db.checkUserExist(usrpsd.at(1))==true)
        {
            str+="fail";
        }
        else
        {
            db.addUser(usrpsd.at(1), usrpsd.at(2));
            str+="success";
        }
        tcpSocket->write(str.toUtf8().data());
    }
    else if(usrpsd.at(0)=="getquestion")
    {
        QString ques=db.getQuestion(usrpsd.at(1));
        tcpSocket->write(ques.toUtf8().data());
    }
    else if(usrpsd.at(0)=="checkanswer")
    {
        QString checkans="checkanswer!@";
        if(db.checkAns(usrpsd.at(1),usrpsd.at(2))==false)
            checkans+="success";
        else
            checkans+="fail";
        tcpSocket->write(checkans.toUtf8().data());
    }
    else if(usrpsd.at(0)=="changepsd")
    {
        db.reSetPass(usrpsd.at(1),usrpsd.at(2));
    }
    else if(usrpsd.at(0)=="changepsdwithlast")
    {
        QString str="changepsdwithlast!@";
        if(db.checkPass(usrpsd.at(1), usrpsd.at(2)))
        {
            db.reSetPass(usrpsd.at(1),usrpsd.at(3));
            str+="success";
            //socket通信建立好后，不用再考虑对方ip，直接用socket套接字发就可
        }
        else str+="fail";
        tcpSocket->write(str.toUtf8().data());
    }
    else if(usrpsd.at(0)=="getalluserinfo")
    {
        QString userinfo;
        QString username=usrpsd.at(1);
        userinfo=QString("getalluserinfo")+sep;
        userinfo+=username+sep;
        userinfo+=db.getTelephone(username)+sep;
        userinfo+=db.getRealName(username)+sep;
        userinfo+=QString("password")+sep;
        userinfo+=db.getQuestion(username)+sep;
        userinfo+=QString("answer");
        qDebug()<<userinfo;
        tcpSocket->write(userinfo.toUtf8().data());

    }

    else if(usrpsd.at(0)=="sendmail")
    {
        usrpsd.removeFirst();
        foreach(QString str,usrpsd)
        {
            if(str=="")
                break;
            QStringList mailInfo=str.split("@#");
            Mail mail;
            QString sender=mailInfo.at(0);
            QString receiver=mailInfo.at(1);
            mail.setSender(sender);
            mail.setReceiver(receiver);
            mail.setTitle(mailInfo.at(2));
            mail.changeCont(mailInfo.at(3));
            //qDebug()<<mail.getSender();
            //qDebug()<<mail.getReceiver();
            //qDebug()<<mail.getCont();
            //qDebug()<<mail.getTitle();
            mail.setTime();
            db.sendMail(mail);
            if(db.checkAutoReply(receiver)==true)
            {

                Mail automail;
                automail.setSender(receiver);
                automail.setReceiver(sender);
                automail.setTitle("AutoReply");
                qDebug()<<db.getAutoReply(receiver);
                automail.changeCont(db.getAutoReply(receiver));
                automail.setTime();
                db.sendMail(automail);
            }
        }
    }
    else if(usrpsd.at(0)=="savedraft")
    {
        usrpsd.removeFirst();
        foreach(QString str,usrpsd)
        {
            if(str=="")
                break;
            QStringList mailInfo=str.split("@#");
            Mail mail;
            mail.setSender(mailInfo.at(0));
            mail.setReceiver(mailInfo.at(1));
            mail.setTitle(mailInfo.at(2));
            mail.changeCont(mailInfo.at(3));
            //qDebug()<<mail.getSender();
            //qDebug()<<mail.getReceiver();
            //qDebug()<<mail.getCont();
            //qDebug()<<mail.getTitle();
            mail.setTime();
            //qDebug()<<100000000000000;
            db.saveDraft(mail);
        }
    }
    else if(usrpsd.at(0)=="receive")
    {
        QList<Mail> maillist=db.receiveMail(usrpsd.at(1),0,15);
        QString mailstr="receive!@";
        foreach(Mail mail ,maillist)
        {
            //qDebug()<<mail.getId();
            mailstr+=mail.getSender()+spm+mail.getReceiver()+spm+mail.getTitle()+spm+mail.getCont()+spm+mail.getTime()+spm;
            if(mail.getIsRead()==true)
                mailstr+="true";
            else mailstr+="false";
            mailstr=mailstr+spm+QString::number(mail.getId());
            mailstr=mailstr+sep;
        }
        //qDebug()<<mailstr;
        tcpSocket->write(mailstr.toUtf8().data());
    }
    else if(usrpsd.at(0)=="receivedrafting")
    {
        QList<Mail> maillist=db.getDraft(usrpsd.at(1),0,15);
        qDebug()<<maillist.count();
        QString mailstr="receivedrafting!@";
        foreach(Mail mail ,maillist)
        {
            //qDebug()<<mail.getId();
            mailstr+=mail.getSender()+spm+mail.getReceiver()+spm+mail.getTitle()+spm+mail.getCont()+spm+mail.getTime()+spm;
            if(mail.getIsRead()==true)
                mailstr+="true";
            else mailstr+="false";
            mailstr=mailstr+spm+QString::number(mail.getId());
            mailstr=mailstr+sep;
        }
        qDebug()<<mailstr;
        tcpSocket->write(mailstr.toUtf8().data());
    }
    else if(usrpsd.at(0)=="receivesending")
    {
       QList<Mail> maillist=db.getSended(usrpsd.at(1),0,15);
       QString mailstr="receivesending!@";
       foreach(Mail mail ,maillist)
       {
           //qDebug()<<mail.getId();
           mailstr+=mail.getSender()+spm+mail.getReceiver()+spm+mail.getTitle()+spm+mail.getCont()+spm+mail.getTime()+spm;
           if(mail.getIsRead()==true)
               mailstr+="true";
           else mailstr+="false";
           mailstr=mailstr+spm+QString::number(mail.getId());
           mailstr=mailstr+sep;
       }
       tcpSocket->write(mailstr.toUtf8().data());
    }
    else if(usrpsd.at(0)=="receivedeleting")
    {
        QList<Mail> maillist=db.getDeleted(usrpsd.at(1),0,15);
        QString mailstr="receivedeleting!@";
        foreach(Mail mail ,maillist)
        {
            //qDebug()<<mail.getId();
            mailstr+=mail.getSender()+spm+mail.getReceiver()+spm+mail.getTitle()+spm+mail.getCont()+spm+mail.getTime()+spm;
            if(mail.getIsRead()==true)
                mailstr+="true";
            else mailstr+="false";
            mailstr=mailstr+spm+QString::number(mail.getId());
            mailstr=mailstr+sep;
        }
        tcpSocket->write(mailstr.toUtf8().data());
    }
    else if(usrpsd.at(0)=="deletemail")
    {
        usrpsd.removeFirst();
        foreach(QString str,usrpsd)
        {
            if(str=="")
                break;
            db.receiverDelete(str.toInt(),1);
        }
    }
    else if(usrpsd.at(0)=="deletesendingmail")
    {
        usrpsd.removeFirst();
        foreach(QString str,usrpsd)
        {
            if(str=="")
                break;
            db.sendDelete(str.toInt(),1);
        }
    }
    else if(usrpsd.at(0)=="undeletemail")
    {
        usrpsd.removeFirst();
        QString username=usrpsd.at(0);
        usrpsd.removeFirst();
        int number;
        foreach(QString str,usrpsd)
        {
            number=str.toInt();
            if(username==db.getSenderById(number))
                db.sendDelete(number,0);
            if(username==db.getRcverById(number))
                db.receiverDelete(number,1);
        }
    }
    else if(usrpsd.at(0)=="setautoreply")
    {
        db.setAutoReply(usrpsd.at(1),usrpsd.at(2));
    }

    else if(usrpsd.at(0)=="addcontact")
    {
        QList<QString> contractlist=db.getContact(usrpsd.at(1));
        //qDebug()<<usrpsd.at(1)<<"     "<<usrpsd.at(2);
        foreach(QString str,contractlist)
        {
            //qDebug()<<str;
            if(str==usrpsd.at(2))
            {
                //qDebug()<<str;
                return;
            }
        }
        db.addIntoList(usrpsd.at(1),usrpsd.at(2));
    }
    else if(usrpsd.at(0)=="showcontact")
    {
        QList<QString> contractlist=db.getContact(usrpsd.at(1));
        //qDebug()<<contractlist.count();
        QString contractstr="showcontact!@";
        foreach(QString username, contractlist)
        {
            //qDebug()<<username;
            contractstr=contractstr+username+spm+db.getTelephone(username);
            contractstr=contractstr+sep;
        }
        qDebug()<<contractstr;
        tcpSocket->write(contractstr.toUtf8().data());
    }
    else if(usrpsd.at(0)=="showblacklist")
    {
        QList<QString> contractlist=db.getBlack(usrpsd.at(1));
        QString contractstr="showblacklist!@";
        foreach(QString username, contractlist)
        {
            contractstr+=username+spm+db.getTelephone(username);
            contractstr+=sep;
        }
        tcpSocket->write(contractstr.toUtf8().data());
    }
    else if(usrpsd.at(0)=="addblacklist")
    {
        usrpsd.removeFirst();
        QString username=usrpsd.at(0);
        usrpsd.removeFirst();
        QStringList contractlist=db.getContact(username);
        QStringList blacklist=db.getBlack(username);
        foreach(QString victim, usrpsd)
        {
            bool flag=false;
            if(victim=="")
                break;
            foreach (QString contract, contractlist)
            {
                if(victim==contract)
                {
                    qDebug()<<1;
                    db.pullBlack(username,victim);
                    flag=true;
                    break;
                }
            }
            foreach (QString black,blacklist)
            {
                if(victim==black)
                {
                    flag=true;
                    qDebug()<<3;
                    break;
                }
            }
            qDebug()<<2;
            if(flag==false)
                db.addBlack(username,victim);
        }
    }
    else if(usrpsd.at(0)=="restoreblacklist")
    {
        usrpsd.removeFirst();
        QString username=usrpsd.at(0);
        usrpsd.removeFirst();
        foreach(QString victim,usrpsd)
        {
            if(victim=="")
                break;
            db.pullWhite(username,victim);
        }
    }
    else if(usrpsd.at(0)=="deletecontact")
    {
        usrpsd.removeFirst();
        QString username=usrpsd.at(0);
        usrpsd.removeFirst();
        foreach(QString victim,usrpsd)
        {
            if(victim=="")
                break;
            db.delFromList(username,victim);
        }
    }
    //qDebug() << usrpsd[0];
    //qDebug() << usrpsd[1];
    //QString opera = usrpsd[0];
    //QString username = usrpsd[1];
    //QString password = usrpsd[2];
    //ui->textEditRead->append(username);
    //ui->textEditRead->append(password);

}
