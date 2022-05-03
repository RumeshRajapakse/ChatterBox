#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QWidget>
#include <QTcpSocket>
#include <login.h>
#include "QListWidgetItem"

namespace Ui {
class ChatWindow;
}

class ChatWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ChatWindow(QWidget *parent = nullptr, QString userName="");
    ~ChatWindow();

    void clearJsonObject(QJsonObject &object);
    void showContacts();
    void showGroups();
    void showOnlineUsers();
    void showChatHistory();
    void showHistory();
    void jsonTest();

    static QString filePath;

public slots:
    void connectToHost(const QString &ip, const QString &port, const QString &user);
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

    void on_btnRefersh_clicked();

    void on_btnRefershRooms_clicked();

    void on_listWidgetOnline_itemDoubleClicked(QListWidgetItem *item);

    void on_listWidgetGroups_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::ChatWindow *ui;

    QTcpSocket _socket;
};

#endif // CHATWINDOW_H
