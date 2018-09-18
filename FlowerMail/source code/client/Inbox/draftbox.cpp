#include "draftbox.h"
#include "ui_draftbox.h"

DraftBox::DraftBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DraftBox)
{
    ui->setupUi(this);
    m_Model=new TableModelForSendBox(this);

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
    connect(ui->tableView,&QTableView::doubleClicked,this,&DraftBox::rowClicked);

}

DraftBox::~DraftBox()
{
    delete ui;
}

void DraftBox::Exec(QStringList list)
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
void DraftBox::rowClicked(const QModelIndex index)
{
    if (index.isValid())
    {
        Mail record = m_Model->recordAt(index.row());
        emit EditMail(record);
    }
}

void DraftBox::on_allSelectButton_clicked()
{
    for(int i=0;i<m_Model->rowCount();i++)
    {
        QModelIndex tempIndex=m_Model->index(i,0);
        m_Model->setData(tempIndex,QVariant(Qt::Checked),Qt::CheckStateRole);
    }
}

void DraftBox::on_deleteButton_clicked()
{
    QList<MailInUI> maillist;
    QList<Mail> deletelist;
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
            deletelist.append(temp);
        }
    }
    m_Model->updateData(maillist);
    //调用删除至已删除列表函数
    MailControl::DeleteSendingMail(deletelist);
}
