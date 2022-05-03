#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTcpServer>
#include <QHash>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void startServer();
    void stopServer();
    bool isListening() const;
    void write(QTcpSocket *socket, const QJsonObject &from);

signals:
     void newMessage(const QByteArray &message);

public slots:
    void sendMessage(const QString &message);

private slots:
    void onNewConnection();
    void onReadyRead();
    void onDisconnected();
    void onNewMessage(const QByteArray &ba);

private:
    QString getClientKey(const QTcpSocket *client ) const;

private:
    Ui::MainWindow *ui;

    QTcpServer _server;
    QHash<QString, QTcpSocket*> _clients;

};
#endif // MAINWINDOW_H
