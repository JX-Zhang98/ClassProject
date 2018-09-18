#include "mailwidget.h"
#include "ui_mailwidget.h"

MailWidget::MailWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MailWidget)
{
    ui->setupUi(this);
    ui->namelabel->setText(UserInfoControl::user.GetUserName());
    QFile qssfile(":/QListStyle.qss");
    qssfile.open(QFile::ReadOnly);
    QString qss;
    qss = qssfile.readAll();
    this->setStyleSheet(qss);
    this->ui->listWidget->setFrameShape(QListWidget::NoFrame);

    sw1=new StackWidgetTest1();
    sw2=new StackWidgetTest2();
    mailEdit=new MailEdit();
    inbox=new Inbox();
    draftBox=new DraftBox();
    sendBox=new SendBox();
    deleteBox=new DeletedBox();
    contractBox=new ContractBox();
    showBox=new ShowBox();
    setBox=new setting();
    blacklist=new BlackContractList();

    ui->stackedWidget->addWidget(sw1);
    ui->stackedWidget->addWidget(sw2);
    ui->stackedWidget->addWidget(mailEdit);
    ui->stackedWidget->addWidget(inbox);
    ui->stackedWidget->addWidget(draftBox);
    ui->stackedWidget->addWidget(sendBox);
    ui->stackedWidget->addWidget(deleteBox);
    ui->stackedWidget->addWidget(contractBox);
    ui->stackedWidget->addWidget(showBox);
    ui->stackedWidget->addWidget(setBox);
    ui->stackedWidget->addWidget(blacklist);

    connect(inbox,&Inbox::ReadMail,this,&MailWidget::ShowMail);
    connect(sendBox,&SendBox::ReadMail,this,&MailWidget::ShowMail);
    connect(deleteBox,&DeletedBox::ReadMail,this,&MailWidget::ShowMail);

    connect(draftBox,&DraftBox::EditMail,this,&MailWidget::EditMail);
    connect(contractBox,&ContractBox::SendTo,this,&MailWidget::EditMailWithRece);
    connect(NetworkSocket::GetTcpSocket(),&QTcpSocket::readyRead,
            [=]()
    {
        QString array=NetworkSocket::ReadMsg();
        qDebug()<<array;
        QStringList list=array.split("!@");
        qDebug()<<list;

    });
}
/*void MailWidget::ReceiveInfo(QString username,QString psd)
{
    ui->label->setText(username);
    ui->label_2->setText(psd);
}*/

MailWidget::~MailWidget()
{
    delete ui;
}

void MailWidget::ShowMail(Mail mail)
{
    showBox->showmail(mail);
    ui->stackedWidget->setCurrentWidget(showBox);
}

void MailWidget::EditMail(Mail mail)
{
    mailEdit->EditMail(mail);
    ui->stackedWidget->setCurrentWidget(mailEdit);
}

void MailWidget::EditMailWithRece(QList<PublicInfo> infolist)
{
    mailEdit->EditMail(infolist);
    ui->stackedWidget->setCurrentWidget(mailEdit);
}

void MailWidget::on_listWidget_clicked(const QModelIndex &index)
{
    int currentRow=ui->listWidget->currentRow()+1;
    switch (currentRow)
    {
        case 1:
            MailControl::ReceiveMail(1);
            ui->stackedWidget->setCurrentWidget(inbox);
            break;
        case 2:
            MailControl::ReceiveMail(2);
            ui->stackedWidget->setCurrentWidget(draftBox);
            break;
        case 3:
            MailControl::ReceiveMail(3);
            ui->stackedWidget->setCurrentWidget(sendBox);
            break;
        case 4:
            MailControl::ReceiveMail(4);
            ui->stackedWidget->setCurrentWidget(deleteBox);
            break;
        case 5:
            ContactlistControl::ShowContact();
            ui->stackedWidget->setCurrentWidget(contractBox);
            break;
        case 6:
            ContactlistControl::ShowBlacklist();
            ui->stackedWidget->setCurrentWidget(blacklist);
            break;
        default:
            break;
    }
}

void MailWidget::on_ConnectButton_clicked()
{

}

void MailWidget::on_WriteButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(mailEdit);
}

void MailWidget::on_ReadButton_clicked()
{
    MailControl::ReceiveMail(1);
}

void MailWidget::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentWidget(setBox);
}
