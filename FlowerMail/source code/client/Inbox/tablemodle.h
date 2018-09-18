#ifndef TABLEMODLE_H
#define TABLEMODLE_H

#include <QAbstractTableModel>
#include "mail.h"
#include "qcommondelegate.h"

class TableModel : public QAbstractTableModel
{
public:
    TableModel(QObject *parent);
    ~TableModel();
    void updateData(QList<MailInUI> recordList);
    int rowCount(const QModelIndex &parent) const;
    int rowCount();
    int columnCount(const QModelIndex &parent) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

    MailInUI recordAt(int row);
private:
    QList<MailInUI> mailList;
};

#endif // TABLEMODLE_H
