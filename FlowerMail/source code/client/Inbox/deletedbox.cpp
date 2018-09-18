#include "deletedbox.h"
#include "ui_deletedbox.h"

DeletedBox::DeletedBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeletedBox)
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
    ui->tableView->setColumnWidth(3,600);
    ui->tableView->setColumnWidth(4,100);
    ui->tableView->setItemDelegate(new QCommonDelegate());

    connect(ui->tableView,&QTableView::doubleClicked,this,&DeletedBox::rowClicked);
}
void DeletedBox::Exec(QStringList list)
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
DeletedBox::~DeletedBox()
{
    delete ui;
}

//行双击事件
void DeletedBox::rowClicked(const QModelIndex index)
{
    if (index.isValid())
    {
        Mail record = m_Model->recordAt(index.row());
        record.setIsread(true);
        QModelIndex tempIndex=m_Model->index(index.row(),1);
        m_Model->setData(tempIndex,QVariant(true),Qt::DisplayRole);
        emit ReadMail(record);
    }
}



void DeletedBox::on_allSelectButton_clicked()
{
    for(int i=0;i<m_Model->rowCount();i++)
    {
        QModelIndex tempIndex=m_Model->index(i,0);
        m_Model->setData(tempIndex,QVariant(Qt::Checked),Qt::CheckStateRole);
    }
}

void DeletedBox::on_recoverButton_clicked()
{
    QList<MailInUI> maillist;
    QList<Mail> recoverlist;
    for(int i=0;i<m_Model->rowCount();i++)
    {
        QModelIndex tempIndex=m_Model->index(i,0);
        MailInUI temp=m_Model->recordAt(tempIndex.row());
        if(temp.getBeChecked()==false)
        {
            maillist.append(temp);
        }
        else
        {
            recoverlist.append(temp);
        }
    }
    m_Model->updateData(maillist);
    //调用恢复至收件箱操作
    MailControl::UndeleteMail(recoverlist);
}

void DeletedBox::on_completeDelButton_clicked()
{
    QList<MailInUI> maillist;
    QList<Mail> completedeletelist;
    for(int i=0;i<m_Model->rowCount();i++)
    {
        QModelIndex tempIndex=m_Model->index(i,0);
        MailInUI temp=m_Model->recordAt(tempIndex.row());
        if(temp.getBeChecked()==false)
        {
            maillist.append(temp);
        }
        else
        {
            completedeletelist.append(temp);
        }
    }
    m_Model->updateData(maillist);
    //调用彻底删除函数
   // emit CompleteDeleteMail(completedeletelist);
}
