#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include "mailwidget.h"
#include "networksocket.h"
#include "userinfocontrol.h"
#include "userinfo.h"


namespace Ui {
class LoginWidget;
}

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = nullptr);
    ~LoginWidget();

private slots:


    void on_ConnectButton_clicked();

private:
    Ui::LoginWidget *ui;
    MailWidget *mailw;
signals:

};

#endif // LOGINWIDGET_H
