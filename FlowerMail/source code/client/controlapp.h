#ifndef CONTROLAPP_H
#define CONTROLAPP_H
#include "mailwidget.h"
#include "Start/loginwidget.h"

class ControlApp:public QObject
{
public:
    ControlApp();
    MailWidget *mailw;
    LoginWidget *loginw;
private:
    void toMailWidget();

};

#endif // CONTROLAPP_H
