#ifndef NETWORKSOCKET_H
#define NETWORKSOCKET_H
#include <QTcpSocket>
#include <QHostAddress>
#include <QStringList>

#define ServerIp "192.168.43.154"
#define ServerPort 8888

class NetworkSocket:public QObject
{
public:
    NetworkSocket();
    ~NetworkSocket();
    static void ConnectSocket(QString=ServerIp,quint16=ServerPort);
    static void SendMsg(QString);
    static void CloseSocket();
    static QByteArray ReadMsg();
    static QTcpSocket* GetTcpSocket();
private:
    static QTcpSocket *tcpSocket;
};


#endif // NETWORKSOCKET_H
