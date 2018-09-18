#ifndef TABLEMODELFORCONTRACT_H
#define TABLEMODELFORCONTRACT_H

#include <QAbstractTableModel>
#include "publicinfoinui.h"
#include "qcommondelegate.h"

class TableModelForContract : public QAbstractTableModel
{
public:
    TableModelForContract(QObject *parent);
    ~TableModelForContract();
    void updateData(QList<PublicInfoInUI> recordList);
    int rowCount(const QModelIndex &parent) const;
    int rowCount();
    int columnCount(const QModelIndex &parent) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

    PublicInfoInUI recordAt(int row);
    QList<PublicInfoInUI> record();
private:
    QList<PublicInfoInUI> contractList;
};

#endif // TABLEMODELFORCONTRACT_H
