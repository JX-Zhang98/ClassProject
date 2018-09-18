#ifndef CONTRACTBOX_H
#define CONTRACTBOX_H

#include <QWidget>
#include "tablemodelforcontract.h"
#include "contactlistcontrol.h"

namespace Ui {
class ContractBox;
}

class ContractBox : public QWidget
{
    Q_OBJECT

public:
    explicit ContractBox(QWidget *parent = nullptr);
    ~ContractBox();
    void rowClicked(const QModelIndex index);
    void setContractbox();
    void Exec(QStringList);

signals:
    void SendTo(QList<PublicInfo>);
    void MoveToBlackList(QList<PublicInfo>);

private slots:
    void on_allSelectButton_clicked();
    void on_moveButton_clicked();
    void on_sendButton_clicked();

    void on_addButton_clicked();

    void on_deleteButton_clicked();

private:
    Ui::ContractBox *ui;
    TableModelForContract *m_Model;
};

#endif // CONTRACTBOX_H
