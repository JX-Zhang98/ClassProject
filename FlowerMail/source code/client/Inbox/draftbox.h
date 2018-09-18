#ifndef DRAFTBOX_H
#define DRAFTBOX_H

#include <QWidget>
#include "tablemodelforsendbox.h"
#include "mailcontrol.h"

namespace Ui {
class DraftBox;
}

class DraftBox : public QWidget
{
    Q_OBJECT

public:
    explicit DraftBox(QWidget *parent = nullptr);
    ~DraftBox();
    void rowClicked(const QModelIndex index);
    void Exec(QStringList list);

signals:
    void EditMail(Mail mail);
    void DeleteMail(QList<Mail> mail);

private slots:
    void on_allSelectButton_clicked();

    void on_deleteButton_clicked();

private:
    Ui::DraftBox *ui;
    TableModelForSendBox * m_Model;
};

#endif // DRAFTBOX_H
