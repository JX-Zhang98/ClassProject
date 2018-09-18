#define CHECK_BOX_COLUMN 0
#define File_PATH_COLUMN 1
#define Column_Count 5
#include "tablemodle.h"
#include <QColor>

TableModel::TableModel(QObject *parent)
    : QAbstractTableModel(parent)
{

}

TableModel::~TableModel()
{

}

// 更新表格数据
void TableModel::updateData(QList<MailInUI> recordList)
{
    mailList = recordList;
    beginResetModel();
    endResetModel();
}

// 行数
int TableModel::rowCount(const QModelIndex &parent) const
{
    return mailList.count();
}
int TableModel::rowCount()
{
    return mailList.count();
}

// 列数
int TableModel::columnCount(const QModelIndex &parent) const
{
    return Column_Count;
}

// 设置表格项数据
bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;

    int nColumn = index.column();
    MailInUI record = mailList.at(index.row());
    switch (role)
    {
    case Qt::DisplayRole:
        switch (nColumn)
        {
            case 1:
                record.setIsread(value.toBool());
                mailList.replace(index.row(), record);
                emit dataChanged(index, index);
                return true;
            case 2:
                record.setSender(value.toString());
                mailList.replace(index.row(), record);
                emit dataChanged(index, index);
                return true;
            case 3:
                record.setTitle(value.toString());
                mailList.replace(index.row(), record);
                emit dataChanged(index, index);
                return true;
            case 4:
                record.setTime(value.toString());
                mailList.replace(index.row(), record);
                emit dataChanged(index, index);
                return true;
         }
        /*if (nColumn == File_PATH_COLUMN)
        {
            //record.strFilePath = value.toString();

            mailList.replace(index.row(), record);
            emit dataChanged(index, index);
            return true;
        }*/
        break;
    case Qt::CheckStateRole:
        if (nColumn == CHECK_BOX_COLUMN)
        {
            record.setBeChecked((value.toInt() == Qt::Checked));

            mailList.replace(index.row(), record);
            emit dataChanged(index, index);
            return true;
        }
        break;
    default:
        return false;
    }
    return false;
}

// 表格项数据
QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    int nRow = index.row();
    int nColumn = index.column();
    MailInUI record = mailList.at(nRow);

    switch (role)
    {
    case Qt::TextColorRole:
        return QColor(Qt::black);
    case Qt::TextAlignmentRole:
        return QVariant(Qt::AlignLeft | Qt::AlignVCenter);
    case Qt::DisplayRole:
        switch (nColumn)
        {
            case 1:
                if(record.getIsRead())
                    return u8"已读";
                else
                    return u8"未读";
            case 2:
                return  record.getSender();
            case 3:
                return  record.getTitle();
            case 4:
                return  record.getTime();
         }
        /*if (nColumn == File_PATH_COLUMN)
            //return QVariant();
            return record.getCont();*/
        return "";
    case Qt::CheckStateRole:
        if (nColumn == CHECK_BOX_COLUMN)
            return record.getBeChecked() ? Qt::Checked : Qt::Unchecked;
        break;
    default:
        return QVariant();
    }

    return QVariant();
}

// 表头数据
QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    switch (role)
    {
    case Qt::TextAlignmentRole:
        return QVariant(Qt::AlignLeft | Qt::AlignVCenter);
    case Qt::DisplayRole:
        if (orientation == Qt::Horizontal)
        {
            switch (section)
            {
                case 0:
                    return  QStringLiteral("");
                case 1:
                    return  QStringLiteral("状态");
                case 2:
                    return  QStringLiteral("发件人");
                case 3:
                    return  QStringLiteral("主题");
                case 4:
                    return  QStringLiteral("时间");
            }
            /*if (section == CHECK_BOX_COLUMN)
                return QStringLiteral("状态");

            if (section == File_PATH_COLUMN)
                return QStringLiteral("文件路径");*/
        }
        break;
    default:
        return QVariant();
    }

    return QVariant();
}

// 表格可选中、可复选
Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return QAbstractItemModel::flags(index);

    Qt::ItemFlags flags = Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    if (index.column() == CHECK_BOX_COLUMN)
        flags |= Qt::ItemIsUserCheckable;

    return flags;
}

MailInUI TableModel::recordAt(int row)
{
    return mailList.at(row);
}
