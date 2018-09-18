#ifndef BLACKLISTBOX_H
#define BLACKLISTBOX_H

#include <QWidget>
#include "tablemodle.h"

namespace Ui {
class BlackListBox;
}

class BlackListBox : public QWidget
{
    Q_OBJECT

public:
    explicit BlackListBox(QWidget *parent = nullptr);
    ~BlackListBox();
    void SetBlackListMail();
    void rowClicked(const QModelIndex index);
    void Exec(QStringList);

signals:
    void ReadMail(Mail mail);
    void MoveMail(QList<Mail> deleteMailList);
    void CompleteDeleteMail(QList<Mail> deleteMailList);

private slots:
    void on_allSelectButton_clicked();

    void on_completeDeleteButton_clicked();

    void on_moveButton_clicked();

private:
    Ui::BlackListBox *ui;
    TableModel *m_Model;
};

#endif // BLACKLISTBOX_H
