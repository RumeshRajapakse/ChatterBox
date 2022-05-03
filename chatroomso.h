#ifndef CHATROOMSO_H
#define CHATROOMSO_H

#include <QDialog>
#include "QListWidgetItem"

namespace Ui {
class ChatRooms;
}

class ChatRooms : public QDialog
{
    Q_OBJECT

public:
    explicit ChatRooms(QWidget *parent = nullptr);
    ~ChatRooms();

    void showAllUsers();
    bool addChatRoom(QString, QString);

    static QString filePath;

private slots:
    void on_btnExit_clicked();

    void on_listAllUsers_itemDoubleClicked(QListWidgetItem *item);

    void on_btnSaveChatRoom_clicked();

private:
    Ui::ChatRooms *ui;
};

#endif // CHATROOMSO_H
