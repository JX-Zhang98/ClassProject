#include "blackcontractlist.h"
#include "ui_blackcontractlist.h"

BlackContractList::BlackContractList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BlackContractList)
{
    ui->setupUi(this);

    m_Model=new TableModelForContract(this);

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
    ui->tableView->setColumnWidth(1,400);
    ui->tableView->setColumnWidth(2,400);
    ui->tableView->setItemDelegate(new QCommonDelegate());
    SetBlackContract();
}

BlackContractList::~BlackContractList()
{
    delete ui;
}

void BlackContractList::SetBlackContract()
{
    QList<PublicInfo> MailList;     //由查看黑名单函数返回
    QList<PublicInfoInUI> List;
    foreach(PublicInfo m , MailList)
    {
        PublicInfoInUI now(m);
        List.append(now);
    }
    /*
    PublicInfoInUI a;
    for(int i=1;i<=5;i++)
    {
        a.SetUserName(QString::number(i));
        List.append(a);
    }
    */
    m_Model->updateData(List);
}

void BlackContractList::on_allSelectButton_clicked()
{
    for(int i=0;i<m_Model->rowCount();i++)
    {
        QModelIndex tempIndex=m_Model->index(i,0);
        m_Model->setData(tempIndex,QVariant(Qt::Checked),Qt::CheckStateRole);
    }
}

void BlackContractList::on_moveButton_clicked()
{
    QList<PublicInfoInUI> maillist;
    QList<PublicInfo> backlist;
    for(int i=0;i<m_Model->rowCount();i++)
    {
        QModelIndex tempIndex=m_Model->index(i,0);
        PublicInfoInUI temp=m_Model->recordAt(tempIndex.row());
        if(temp.getBeChecked()==false)
        {
            maillist.append(temp);
        }
        else
        {
            backlist.append(temp);
        }
    }
    m_Model->updateData(maillist);
    //调用移动回通讯录函数
    ContactlistControl::RestoreBlacklist(backlist);
}

void BlackContractList::Exec(QStringList list)
{
    list.removeAt(0);
    QList<PublicInfoInUI> infolist;
    foreach(QString str,list)
    {
        if(str=="")
            break;
        QStringList publicInfo=str.split("@#");
        PublicInfoInUI info;
       info.SetUserName(publicInfo.at(0));
       info.SetPhoneNumber(publicInfo.at(1));
       infolist.append(info);
    }
    m_Model->updateData(infolist);
}
