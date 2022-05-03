#ifndef CHATDASHBOARD_H
#define CHATDASHBOARD_H

#include <QDialog>
#include <QTcpSocket>

namespace Ui {
class ChatDashboard;
}

class ChatDashboard : public QDialog
{
    Q_OBJECT

public:
    explicit ChatDashboard(QWidget *parent = nullptr);
    ~ChatDashboard();

    void clearJsonObject(QJsonObject &object);
    void showContacts();
    void showGroups();
    void showOnlineUsers();
    void showChatHistory();
    void showHistory();
    void jsonTest();

    static QString filePath;

public slots:
    void connectToHost(const QString &ip, const QString &port);
    void sendMessage(const QString &message);

    void onConnected();
    void onErrorOccurred(QAbstractSocket::SocketError error);
    void onReadyRead();

signals:
    void newMessage(const QByteArray &ba);

private slots:

    void on_btnEditProfle_clicked();

    void on_btnViewChatHistory_clicked();

    void on_btnChatRooms_clicked();

    void on_btnSaveChatHistory_clicked();

    void on_sendButton_clicked();

    void on_btnSignOut_clicked();

private:
    Ui::ChatDashboard *ui;

    QTcpSocket _socket;
};

#endif // CHATDASHBOARD_H
