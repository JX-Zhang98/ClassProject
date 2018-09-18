#ifndef DELETEDBOX_H
#define DELETEDBOX_H

#include <QWidget>
#include "tablemodle.h"
#include "mailcontrol.h"

namespace Ui {
class DeletedBox;
}

class DeletedBox : public QWidget
{
    Q_OBJECT

public:
    explicit DeletedBox(QWidget *parent = nullptr);
    ~DeletedBox();
    void rowClicked(const QModelIndex index);
    void Exec(QStringList list);

signals:
    void ReadMail(Mail mail);
    void RecoverMail(QList<Mail> deleteMailList);
    void CompleteDeleteMail(QList<Mail> deleteMailList);


private slots:
    void on_allSelectButton_clicked();
    void on_recoverButton_clicked();
    void on_completeDelButton_clicked();

private:
    Ui::DeletedBox *ui;
    TableModel *m_Model;
};

#endif // DELETEDBOX_H
