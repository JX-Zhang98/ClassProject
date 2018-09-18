#ifndef ADDUSER_H
#define ADDUSER_H

#include <QWidget>
#include <QMessageBox>
#include "userinfocontrol.h"

namespace Ui {
class addUser;
}

class addUser : public QWidget
{
    Q_OBJECT

public:
    explicit addUser(QWidget *parent = 0);
    ~addUser();
    void Exec(QString);

private slots:
    void on_ok_in_clicked();

private:
    Ui::addUser *ui;
};

#endif // ADDUSER_H
