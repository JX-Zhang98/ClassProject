#ifndef QCOMMONDELEGATE_H
#define QCOMMONDELEGATE_H

#include <QStyledItemDelegate>

class QCommonDelegate : public QStyledItemDelegate
{
    Q_OBJECT

    public:
        QCommonDelegate(QObject *parent=nullptr): QStyledItemDelegate(parent) {}
        ~QCommonDelegate(){}

    private:

        void paint(QPainter *painter,
            const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // QCOMMONDELEGATE_H
