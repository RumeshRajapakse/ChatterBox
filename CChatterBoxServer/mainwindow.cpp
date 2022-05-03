#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&_server, &QTcpServer::newConnection, this, &MainWindow::onNewConnection);
    connect(this, &MainWindow::newMessage, this, &MainWindow::onNewMessage);
    if(_server.listen(QHostAddress::Any, 3500))
    {
        qInfo() << "Listening...";
        ui->listServerLog->appendPlainText("Listening...");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendMessage(const QString &message)
{
    emit newMessage("\nServer:" + message.toUtf8());
    qInfo() << message.toUtf8();
}

void MainWindow::onNewConnection()
{
    const auto client = _server.nextPendingConnection();
    if(client == nullptr)
    {
        return;
    }

    qInfo() << "New Client connected";
    ui->listServerLog->appendPlainText("New Client connected");

    _clients.insert(this->getClientKey(client), client);

    connect(client, &QTcpSocket::readyRead, this, &MainWindow::onReadyRead);
    connect(client, &QTcpSocket::disconnected, this, &MainWindow::onDisconnected);
}

void MainWindow::onReadyRead()
{
    const auto client = qobject_cast<QTcpSocket*>(sender());
    if(client == nullptr)
    {
      return;
    }

     const auto message = this->getClientKey(client).toUtf8() + ": " + client->readAll();

    emit newMessage(message);
}

void MainWindow::onDisconnected()
{
    const auto client = qobject_cast<QTcpSocket*>(sender());
    if(client == nullptr)
    {
        return;
    }

    _clients.remove(this->getClientKey(client));
}

void MainWindow::onNewMessage(const QByteArray &ba)
{
    for(const auto &client : qAsConst (_clients)){
        client->write(ba);
        client->flush();
    }
}

QString MainWindow::getClientKey(const QTcpSocket *client) const
{
    return client->peerAddress().toString().append(":").append(QString::number(client->peerPort()));
}
