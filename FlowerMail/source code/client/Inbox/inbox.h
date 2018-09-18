#ifndef INBOX_H
#define INBOX_H

#include <QWidget>
#include <QWindow>
#include <QTimer>
#include "tablemodle.h"
#include "mailcontrol.h"

namespace Ui {
class Inbox;
}

class Inbox : public QWidget
{
    Q_OBJECT

public:
    explicit Inbox(QWidget *parent = nullptr);
    ~Inbox();
    void rowClicked(const QModelIndex index);

    int GetUnread();
    void Exec(QStringList list);

signals:
    void ReadMail(Mail mail);
    void DeleteMail(QList<Mail> MailList);
    void ChangeToReadMailList(QList<Mail> MailList);

private slots:
    void on_receiveButton_clicked();
    void on_allSelectButton_clicked();
    void on_deleteButton_clicked();
    void on_hasReadButton_clicked();

private:
    Ui::Inbox *ui;
    TableModel *m_Model;
    QTimer * receiveWithTime;
    int unRead;
};

#endif // INBOX_H
