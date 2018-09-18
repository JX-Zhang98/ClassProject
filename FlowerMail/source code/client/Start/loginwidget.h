#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <QMessageBox>
#include "findpwdwindow.h"
#include "adduser.h"
#include "userinfocontrol.h"

namespace Ui {
class LoginWidget;
}

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = 0);
    FindpwdWindow *findpsd;
    //加入主界面
    addUser *regis;        //注册

    void Exec(QString);
    ~LoginWidget();


private slots:

    void on_loginButton_clicked();

    void on_registerButton_clicked();

    void on_findpsdButton_clicked();

private:
    Ui::LoginWidget *ui;
signals:
    void sendtocontrol();
};

#endif // LOGINWIDGET_H
