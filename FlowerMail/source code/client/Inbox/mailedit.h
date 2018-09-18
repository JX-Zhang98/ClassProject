#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QListWidgetItem>
#include <QMessageBox>
#include "networksocket.h"
#include "userinfocontrol.h"
#include "mailcontrol.h"
#include "mail.h"

namespace Ui {
class MailEdit;
}

class MailEdit : public QWidget
{
    Q_OBJECT

public:
    explicit MailEdit(QWidget *parent = nullptr);
    ~MailEdit();
    void EditMail(Mail);
    void EditMail(QList<PublicInfo>);
    void Clear();

signals:
    void SendMailList(QList<Mail>);
    void DraftMailList(QList<Mail>);

private slots:
    void on_sendMailButton_clicked();
    void on_draftButton_clicked();

private:
    Ui::MailEdit *ui;

};

#endif // MAINWINDOW_H
