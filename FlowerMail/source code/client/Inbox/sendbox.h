#ifndef SENDBOX_H
#define SENDBOX_H

#include <QWidget>
#include "tablemodelforsendbox.h"
#include "mailcontrol.h"

namespace Ui {
class SendBox;
}

class SendBox : public QWidget
{
    Q_OBJECT

public:
    explicit SendBox(QWidget *parent = nullptr);
    ~SendBox();
    void rowClicked(const QModelIndex index);
    void Exec(QStringList list);

signals:
    void ReadMail(Mail mail);
    void DeleteMail(QList<Mail> deleteMailList);

private slots:
    void on_allSelectButton_clicked();
    void on_deleteButton_clicked();

private:
    Ui::SendBox *ui;
    TableModelForSendBox * m_Model;
};

#endif // SENDBOX_H
