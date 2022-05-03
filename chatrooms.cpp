#include "chatrooms.h"
#include "ui_chatrooms.h"
#include "chatwindow.h"
#include "QFile"
#include "QJsonDocument"
#include "QJsonObject"
#include "QDebug"
#include "QJsonArray"
#include "QListWidgetItem"
#include "QMessageBox"
#include "QList"

QString roomName;
QJsonArray userschat;
QString ChatRooms::filePath = "/home/rumesh/Downloads/Latest 1/Latest/CChatterBox/";

ChatRooms::ChatRooms(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatRooms)
{
    ui->setupUi(this);

    showAllUsers();
}

ChatRooms::~ChatRooms()
{
    delete ui;
}

void ChatRooms::showAllUsers()
{
    QString val;
    QString chatContact;

          QFile file;
          file.setFileName(filePath + "Contacts.json");
          file.open(QIODevice::ReadOnly | QIODevice::Text);
          val = file.readAll();
          file.close();
          QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
          QJsonObject rootObj = d.object();
          QJsonArray ptsArray = rootObj.value("contacts").toArray();

          foreach(const QJsonValue & val, ptsArray){
                  chatContact=val.toObject().value("UserName").toString();
                   ui->listUsers->addItem(chatContact);
            }
}

void ChatRooms::on_listAllUsers_itemDoubleClicked(QListWidgetItem *item)
{
//    qDebug()<< item << endl;
    item->setBackgroundColor(QColor(128,128,255));

       QMessageBox messageBox;
       messageBox.setWindowTitle("Chat Room");
       messageBox.setText("Successfully added " + item->text() + " to chat room");
       messageBox.setStandardButtons(QMessageBox::Yes);
       messageBox.setDefaultButton(QMessageBox::No);
       if(messageBox.exec() == QMessageBox::Yes){


       }
       else {


       }
}

void ChatRooms::on_btnSaveChatRoom_clicked()
{
    roomName = ui->txtChatRoomname->text();
    if(roomName.isEmpty())
    {
        QMessageBox::warning(this, "Chat Rooms", "Room Name cannot be empty");
    }
    else{

        QMessageBox messageBox;
        messageBox.setWindowTitle("Chat Room");
        messageBox.setText("Successfully created " + roomName + " chat room");
        messageBox.setStandardButtons(QMessageBox::Yes);
        messageBox.setDefaultButton(QMessageBox::No);
        if(messageBox.exec() == QMessageBox::Yes){

          addChatRoom(roomName,userschat);

          hide();
          ChatWindow *chatWindow = new ChatWindow();
          chatWindow->show();

        }
        else {

            hide();
            ChatWindow *chatWindow = new ChatWindow();
            chatWindow->show();
        }

    }
}

bool ChatRooms::addChatRoom(QString room_name, QJsonArray users){

        QJsonArray jsonArray;
        QJsonArray usersArray;
        QJsonObject rootObject;
        QJsonObject branchObject;
        QJsonObject leafObject;
        QJsonArray chatUsers = { "Rumesh", "Pabasara", "Pabasara" };

        branchObject.insert("RoomName", room_name);
        branchObject.insert("users", chatUsers);
//        branchObject.insert("users", users);
        jsonArray.append(branchObject);

        rootObject.insert("ChatRooms", jsonArray);
        QJsonDocument jsonDocument;
        jsonDocument.setObject(rootObject);
        QByteArray byteArray = jsonDocument.toJson(QJsonDocument::Indented);
        QFile file;
//        file.setFileName(filePath + "test.json");
         file.setFileName(filePath + "Groups.json");
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
        {
            qDebug() << QString("fail to open the file: %1, %2, %3").arg(__FILE__).arg(__LINE__).arg(__FUNCTION__);
//            return;
        }
        QTextStream out(&file);
        out << byteArray;
        file.close();
        qDebug() << byteArray;



}

void ChatRooms::on_btnExit_clicked()
{
    hide();
    ChatWindow *chatWindow = new ChatWindow();
    chatWindow->show();
}



void ChatRooms::on_listUsers_itemDoubleClicked(QListWidgetItem *item)
{

    QString tests =  ui->listUsers->currentItem()->text();
    //  qDebug()<< tests << endl;

        QStringList lstUsers;

        lstUsers << tests;

        ui->listAllRoomUsers->addItems(lstUsers);

        for(int i = 0; i < ui->listAllRoomUsers->count(); i++)
           {
               QListWidgetItem* item = ui->listAllRoomUsers->item(i);
       //        qDebug()<< "item" << item->text();
               userschat.append(item->text());
               qDebug()<< "chattUsers" << userschat;
           }



    item->setBackgroundColor(QColor(128,128,255));

       QMessageBox messageBox;
       messageBox.setWindowTitle("Chat Room");
       messageBox.setText("Successfully added " + item->text() + " to chat room");
       messageBox.setStandardButtons(QMessageBox::Yes);
       messageBox.setDefaultButton(QMessageBox::No);
       if(messageBox.exec() == QMessageBox::Yes){


       }
       else {


       }
}



