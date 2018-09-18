#include "mailwidget.h"
#include "commonhelper.h"
#include "networksocket.h"
#include "controlapp.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NetworkSocket socket;
    NetworkSocket::ConnectSocket();
    ControlApp control;
    //MailWidget m;
   // m.show();
    return a.exec();
}
