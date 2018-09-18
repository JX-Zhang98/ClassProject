#include "networksocket.h"
QTcpSocket* NetworkSocket::tcpSocket=nullptr;
NetworkSocket::NetworkSocket()
{
    tcpSocket=new QTcpSocket();
}
NetworkSocket::~NetworkSocket()
{
    delete tcpSocket;
}

void NetworkSocket::ConnectSocket(QString ip,quint16 port)
{
    tcpSocket->connectToHost(QHostAddress(ip),port);

}
void NetworkSocket::SendMsg(QString msg)
{
    tcpSocket->write(msg.toUtf8().data());
}
QByteArray NetworkSocket::ReadMsg()
{
    return tcpSocket->readAll();
}
void NetworkSocket::CloseSocket()
{
    if(tcpSocket==nullptr)
        return;
    tcpSocket->disconnectFromHost();
    tcpSocket->close();
}
QTcpSocket* NetworkSocket::GetTcpSocket()
{
    return tcpSocket;
}
