#ifndef MAILWIDGET_H
#define MAILWIDGET_H

#include <QWidget>
#include <QFile>
#include"stackwidgettest1.h"
#include"stackwidgettest2.h"
#include"Inbox/mailedit.h"
#include"subwidget.h"
#include "userinfocontrol.h"
#include "mailcontrol.h"
#include "contactlistcontrol.h"

namespace Ui {
class MailWidget;
}

class MailWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MailWidget(QWidget *parent = nullptr);
    ~MailWidget();
    //void ReceiveInfo(QString,QString);
    void ShowMail(Mail);
    void EditMail(Mail);
    void EditMailWithRece(QList<PublicInfo>);

    StackWidgetTest1 *sw1;
    StackWidgetTest2 *sw2;
    MailEdit *mailEdit;
    Inbox *inbox;
    DraftBox *draftBox;
    SendBox *sendBox;
    DeletedBox *deleteBox;
    ContractBox *contractBox;
    BlackContractList *blacklist;
    ShowBox *showBox;
    setting *setBox;

private slots:
    void on_listWidget_clicked(const QModelIndex &index);
    void on_ConnectButton_clicked();
    void on_WriteButton_clicked();
    void on_ReadButton_clicked();
    
    void on_pushButton_3_clicked();

private:
    Ui::MailWidget *ui;

};

#endif // MAILWIDGET_H
