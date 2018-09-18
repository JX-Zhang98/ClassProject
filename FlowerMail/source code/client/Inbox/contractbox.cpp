#include "contractbox.h"
#include "ui_contractbox.h"

ContractBox::ContractBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ContractBox)
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

    connect(ui->tableView,&QTableView::doubleClicked,this,&ContractBox::rowClicked);
    setContractbox();
}

ContractBox::~ContractBox()
{
    delete ui;
}

void ContractBox::rowClicked(const QModelIndex index)
{
    if (index.isValid())
    {
        QList<PublicInfo> temp;
        PublicInfoInUI record = m_Model->recordAt(index.row());
        temp.append(record);
        emit SendTo(temp);
    }
}

void ContractBox::on_allSelectButton_clicked()
{
    for(int i=0;i<m_Model->rowCount();i++)
    {
        QModelIndex tempIndex=m_Model->index(i,0);
        m_Model->setData(tempIndex,QVariant(Qt::Checked),Qt::CheckStateRole);
    }
}

void ContractBox::setContractbox()
{
    QList<PublicInfo> MailList;    //由查看通讯录信息返回
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
        a.SetUserName("2222");
        a.SetPhoneNumber("1111");
        List.append(a);
    }
*/
    m_Model->updateData(List);
}

void ContractBox::on_moveButton_clicked()
{
    QList<PublicInfoInUI> maillist;
    QList<PublicInfo> blacklist;
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
            blacklist.append(temp);
        }
    }
    m_Model->updateData(maillist);
    //调用移入黑名单函数
    ContactlistControl::AddBlacklist(blacklist);
}

void ContractBox::on_sendButton_clicked()
{
    QList<PublicInfoInUI> maillist;
    QList<PublicInfo> receiverlist;
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
            receiverlist.append(temp);
        }
    }
    m_Model->updateData(maillist);
    emit SendTo(receiverlist);
}

void ContractBox::on_addButton_clicked()
{
    QString addByUserName=ui->addEdit->text();
    if(addByUserName=="")
        return;
    //调用添加通讯录的操作
    ContactlistControl::AddContact(addByUserName);

    ContactlistControl::AddContact(addByUserName);
    PublicInfoInUI addcontract;
    addcontract.SetUserName(addByUserName);
    addcontract.SetPhoneNumber("");
    addcontract.setBeChecked(false);
    QList<PublicInfoInUI> infolist=m_Model->record();
    infolist.append(addcontract);
    m_Model->updateData(infolist);
    //ContactlistControl::ShowContact();
    //ContactlistControl::ShowContact();
}

void ContractBox::on_deleteButton_clicked()
{
    QList<PublicInfoInUI> maillist;
    QList<PublicInfo> deletelist;
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
            deletelist.append(temp);
        }
    }
    m_Model->updateData(maillist);
    ContactlistControl::DeleteContact(deletelist);
}
void ContractBox::Exec(QStringList list)
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
