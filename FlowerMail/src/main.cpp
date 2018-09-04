#include "mainwindow.h"
#include <QApplication>
# include "databs.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    Databs v;
    v.addUser("硕神", "123456", "liushuo", "911");
    v.checkUserExist("pn");
    v.checkPass("硕神", "123456");
    //v.setInfo()
    return a.exec();
}
