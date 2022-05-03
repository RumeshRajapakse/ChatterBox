#include "tcpclient.h"


TCPclient::TCPclient(QObject *parent)
    : QObject{parent}
{
    connect(&_socket, &QTcpSocket::connected, this, &TCPclient::onConnected);
  //  connect(&_socket, &QTcpSocket::errorOccurred, this, &TCPclient::onErrorOccurred);
    connect(&_socket, &QTcpSocket::readyRead, this, &TCPclient::onReadyRead);
}

void TCPclient::connectToHost(const QString &ip, const QString &port)
{
    _socket.connectToHost(ip, port.toUInt());
}

void TCPclient::sendMessage(const QString &message)
{
    _socket.write(message.toUtf8());
    _socket.flush();
}

void TCPclient::onConnected()
{
    qInfo() << "Connected to host";
}

void TCPclient::onErrorOccurred(QAbstractSocket::SocketError error)
{
    qWarning() << "Error:" << error;
}

void TCPclient::onReadyRead()
{
    const auto message = _socket.readAll();
    emit newMessage(message);
}
