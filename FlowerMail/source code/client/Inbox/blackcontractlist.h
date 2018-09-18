#ifndef BLACKCONTRACTLIST_H
#define BLACKCONTRACTLIST_H

#include <QWidget>
#include "tablemodelforcontract.h"
#include "contactlistcontrol.h"

namespace Ui {
class BlackContractList;
}

class BlackContractList : public QWidget
{
    Q_OBJECT

public:
    explicit BlackContractList(QWidget *parent = nullptr);
    ~BlackContractList();
    void SetBlackContract();
    void Exec(QStringList);

signals:
    void MoveBack(QList<PublicInfo>);
    void Delete(QList<PublicInfo>);

private slots:
    void on_allSelectButton_clicked();
    void on_moveButton_clicked();

private:
    Ui::BlackContractList *ui;
    TableModelForContract *m_Model;
};

#endif // BLACKCONTRACTLIST_H
