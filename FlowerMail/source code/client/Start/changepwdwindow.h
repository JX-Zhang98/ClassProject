#ifndef CHANGEPWDWINDOW_H
#define CHANGEPWDWINDOW_H

#include <QWidget>
#include <QMessageBox>
#include "userinfocontrol.h"

namespace Ui {
class ChangepwdWindow;
}

class ChangepwdWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ChangepwdWindow(QWidget *parent = 0);
    void setusername(QString);
    ~ChangepwdWindow();
    void Exec(QString);

private slots:
    void on_ok_clicked();

private:
    Ui::ChangepwdWindow *ui;
};

#endif // CHANGEPWDWINDOW_H
