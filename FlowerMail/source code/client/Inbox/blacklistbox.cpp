#include "blacklistbox.h"
#include "ui_blacklistbox.h"

BlackListBox::BlackListBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BlackListBox)
{
    ui->setupUi(this);
    m_Model=new TableModel(this);

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

    connect(ui->tableView,&QTableView::doubleClicked,this,&BlackListBox::rowClicked);
    SetBlackListMail();
}

BlackListBox::~BlackListBox()
{
    delete ui;
}

void BlackListBox::rowClicked(const QModelIndex index)
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

void BlackListBox::SetBlackListMail()
{
    QList<Mail> MailList;    //由查看黑名单邮件列表返回
    QList<MailInUI> List;
    foreach(Mail m , MailList)
    {
        MailInUI now(m);
        List.append(now);
    }
    /*
    MailInUI a;
    for(int i=1;i<=5;i++)
    {
        a.setTitle(QString::number(i));
        a.setIsread(false);
        List.append(a);
    }*/
    m_Model->updateData(List);
}
void BlackListBox::on_allSelectButton_clicked()
{
    for(int i=0;i<m_Model->rowCount();i++)
    {
        QModelIndex tempIndex=m_Model->index(i,0);
        m_Model->setData(tempIndex,QVariant(Qt::Checked),Qt::CheckStateRole);
    }
}

void BlackListBox::on_completeDeleteButton_clicked()
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
    //调用彻底删除邮件
    //emit CompleteDeleteMail(completedeletelist);
}

void BlackListBox::on_moveButton_clicked()
{
    QList<MailInUI> maillist;
    QList<Mail> movelist;
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
            movelist.append(temp);
        }
    }
    m_Model->updateData(maillist);
    //调用移动移入收件箱操作
    //emit MoveMail(movelist);
}
void BlackListBox::Exec(QStringList list)
{
}
