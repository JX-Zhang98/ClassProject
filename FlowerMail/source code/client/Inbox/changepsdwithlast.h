#ifndef CHANGEPSDWITHLAST_H
#define CHANGEPSDWITHLAST_H

#include <QWidget>

namespace Ui {
class ChangePsdWithLast;
}

class ChangePsdWithLast : public QWidget
{
    Q_OBJECT

public:
    explicit ChangePsdWithLast(QWidget *parent = nullptr);
    ~ChangePsdWithLast();
    void Exec(QString);

private:
    Ui::ChangePsdWithLast *ui;
};

#endif // CHANGEPSDWITHLAST_H
