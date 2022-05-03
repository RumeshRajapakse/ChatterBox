#ifndef CHATROOMS_H
#define CHATROOMS_H

#include <QWidget>
#include "QListWidgetItem"

namespace Ui {
class ChatRooms;
}

class ChatRooms : public QWidget
{
    Q_OBJECT

public:
    explicit ChatRooms(QWidget *parent = nullptr);
    ~ChatRooms();

    void showAllUsers();
    bool addChatRoom(QString, QJsonArray);

    static QString filePath;

private slots:
    void on_btnExit_clicked();

    void on_listAllUsers_itemDoubleClicked(QListWidgetItem *item);


    void on_listUsers_itemDoubleClicked(QListWidgetItem *item);


    void on_btnSaveChatRoom_clicked();

private:
    Ui::ChatRooms *ui;
};

#endif // CHATROOMS_H
