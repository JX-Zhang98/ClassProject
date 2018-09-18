#define Every_Receive_Time 60*1000
#include "inbox.h"
#include "ui_inbox.h"
#include "networksocket.h"
#include <QDebug>
#include <QMessageBox>

Inbox::Inbox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Inbox)
{
    ui->setupUi(this);
    m_Model=new TableModel(this);

    //设置表格格式
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->horizontalHeader()->setHighlightSections(false);
    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->setShowGrid(false);
    ui->tableView->setFrameShape(QFrame::NoFrame);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setModel(m_Model);
    ui->tableView->setColumnWidth(0,15);
    ui->tableView->setColumnWidth(1,50);
    ui->tableView->setColumnWidth(3,500);
    ui->tableView->setColumnWidth(4,100);
    ui->tableView->setItemDelegate(new QCommonDelegate());
    connect(ui->tableView,&QTableView::doubleClicked,this,&Inbox::rowClicked);
    //定时收件
    //receiveWithTime=new QTimer();
    //connect(receiveWithTime,&QTimer::timeout,this,&Inbox::ReceiveMail);
   // receiveWithTime->start(Every_Receive_Time);
}

Inbox::~Inbox()
{
    delete ui;
}
void Inbox::Exec(QStringList list)
{
    list.removeAt(0);
    QList<MailInUI> maillist;
    foreach(QString str,list)
    {
        if(str=="")
            break;
        QStringList mailInfo=MailControl::MailSplit(str);
        MailInUI mail;
        mail.setBeChecked(false);
        mail.setSender(mailInfo.at(0));
        mail.setReceiver(mailInfo.at(1));
        mail.setTitle(mailInfo.at(2));
        mail.changeCont(mailInfo.at(3));
        mail.setTime(mailInfo.at(4));
        if(mailInfo.at(5)=="true")
            mail.setIsread(true);
        else
            mail.setIsread(false);
        mail.setId(mailInfo.at(6).toInt());
        maillist.append(mail);

    }
    m_Model->updateData(maillist);
}

//行双击事件
void Inbox::rowClicked(const QModelIndex index)
{
    if (index.isValid())
    {
        Mail record = m_Model->recordAt(index.row());
        record.setIsread(true);
        QModelIndex tempIndex=m_Model->index(index.row(),1);
        m_Model->setData(tempIndex,QVariant(true),Qt::DisplayRole);
        unRead--;
        emit ReadMail(record);
    }
}



//收件按钮点击事件
void Inbox::on_receiveButton_clicked()
{
    MailControl::ReceiveMail(1);
}

//全选按钮
void Inbox::on_allSelectButton_clicked()
{
    for(int i=0;i<m_Model->rowCount();i++)
    {
        QModelIndex tempIndex=m_Model->index(i,0);
        m_Model->setData(tempIndex,QVariant(Qt::Checked),Qt::CheckStateRole);
    }
}

void Inbox::on_deleteButton_clicked()
{
    QList<MailInUI> maillist;
    QList<Mail> deletelist;
    unRead=0;
    for(int i=0;i<m_Model->rowCount();i++)
    {
        QModelIndex tempIndex=m_Model->index(i,0);
        MailInUI temp=m_Model->recordAt(tempIndex.row());
        if(temp.getBeChecked()==false)
        {
            maillist.append(temp);
            if(temp.getIsRead()==false)
                unRead++;
        }
        else
        {
            deletelist.append(temp);
        }
    }
    m_Model->updateData(maillist);
    //调用删除至已删除列表函数
    MailControl::DeleteMail(deletelist);
}
//还需要将标记写回数据库
void Inbox::on_hasReadButton_clicked()
{
    QList<MailInUI> maillist;
    QList<Mail> toIsReadMailList;
    for(int i=0;i<m_Model->rowCount();i++)
    {
        QModelIndex tempIndex=m_Model->index(i,0);
        MailInUI temp=m_Model->recordAt(tempIndex.row());
        if(temp.getBeChecked()==true)
        {
            temp.setIsread(true);
            if(temp.getIsRead()==false)
            {
                toIsReadMailList.append(temp);
            }
        }
        maillist.append(temp);
    }
    unRead=0;
    m_Model->updateData(maillist);
    //调用修改已读标志的函数
    MailControl::IsReadMail(toIsReadMailList);
}

int Inbox::GetUnread()
{
   return unRead;
}
