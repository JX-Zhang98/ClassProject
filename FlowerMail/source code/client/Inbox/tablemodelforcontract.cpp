#include "tablemodelforcontract.h"
#define Column_Count 3
#define CHECK_BOX_COLUMN 0

TableModelForContract::TableModelForContract(QObject *parent)
    : QAbstractTableModel(parent)
{

}

TableModelForContract::~TableModelForContract()
{

}

// 更新表格数据
void TableModelForContract::updateData(QList<PublicInfoInUI> recordList)
{
    contractList = recordList;
    beginResetModel();
    endResetModel();
}

// 行数
int TableModelForContract::rowCount(const QModelIndex &parent) const
{
    return contractList.count();
}
int TableModelForContract::rowCount()
{
    return contractList.count();
}

// 列数
int TableModelForContract::columnCount(const QModelIndex &parent) const
{
    return Column_Count;
}

// 设置表格项数据
bool TableModelForContract::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;

    int nColumn = index.column();
    PublicInfoInUI record = contractList.at(index.row());
    switch (role)
    {
    case Qt::DisplayRole:
        switch (nColumn)
        {
            case 1:
                record.SetUserName(value.toString());
                contractList.replace(index.row(), record);
                emit dataChanged(index, index);
                return true;
            case 2:
                record.SetPhoneNumber(value.toString());
                contractList.replace(index.row(), record);
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

            contractList.replace(index.row(), record);
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
QVariant TableModelForContract::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    int nRow = index.row();
    int nColumn = index.column();
    PublicInfoInUI record = contractList.at(nRow);

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
                return  record.GetUserName();
            case 2:
                return  record.GetPhoneNumber();
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
QVariant TableModelForContract::headerData(int section, Qt::Orientation orientation, int role) const
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
                    return  QStringLiteral("用户名");
                case 2:
                    return  QStringLiteral("电话");
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
Qt::ItemFlags TableModelForContract::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return QAbstractItemModel::flags(index);

    Qt::ItemFlags flags = Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    if (index.column() == CHECK_BOX_COLUMN)
        flags |= Qt::ItemIsUserCheckable;

    return flags;
}

PublicInfoInUI TableModelForContract::recordAt(int row)
{
    return contractList.at(row);
}

QList<PublicInfoInUI> TableModelForContract::record()
{
    return contractList;
}
