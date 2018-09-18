#ifndef SERVERWIDGET_H
#define SERVERWIDGET_H

#include <QWidget>
#include <QMessageBox>
#include <QDebug>
#include <QTcpServer>//监听套接字
#include <QTcpSocket>//通信套接字

namespace Ui {
class ServerWidget;
}

class ServerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ServerWidget(QWidget *parent = nullptr);
    ~ServerWidget();

private slots:
    void on_SendButton_clicked();
    void on_CloseButton_clicked();

private:
    Ui::ServerWidget *ui;
    QTcpServer *tcpServer;//监听套接字
    QTcpSocket *tcpSocket;//通信套接字
    void analysis(QString order);
};

#endif // SERVERWIDGET_H
