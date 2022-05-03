#include "chatwindow.h"
#include "ui_chatwindow.h"
#include "login.h"
#include "profile.h"
#include "chatroomso.h"
#include "QFile"
#include "QJsonDocument"
#include "QJsonObject"
#include "QDebug"
#include "QJsonArray"
#include "QThread"
#include "QMessageBox"
#include "QListWidgetItem"

QString loggedUser;
QString ggloggedUser;
QString nloggedUser;
QString sloggedUser = "";
QStringList groupChats;
QStringList groupChatUsers;
QStringList groupChatMessages;

QString ChatWindow::filePath = "/home/rumesh/Downloads/Latest 1/Latest/CChatterBox/";

ChatWindow::ChatWindow(QWidget *parent, QString userName) :
    QWidget(parent),
    ui(new Ui::ChatWindow)
{
    ui->setupUi(this);

    connect(&_socket, &QTcpSocket::connected, this, &ChatWindow::onConnected);

    connect(&_socket, &QTcpSocket::readyRead, this, &ChatWindow::onReadyRead);

    showContacts();
    showGroups();
//    showOnlineUsers();
     ui->listWidgetOnline->addItem("Rumesh");
    connectToHost("127.0.0.1", "3500", userName);
    ui->listWidgetMessages->addItem("Connected to host");
    loggedUser = userName;
    if(loggedUser == "Rumesh")
       {
        ggloggedUser = "Pabasara";
    }
    else if(loggedUser == "Pabasara"){
        ggloggedUser = "Rumesh";
    }
    else if(loggedUser == "Shashi"){
          ggloggedUser = "Shashi";
      }

    ui->lblUserName->setText(ggloggedUser);
}

ChatWindow::~ChatWindow()
{
    delete ui;
}

void ChatWindow::on_btnEditProfle_clicked()
{
    hide();
    Profile *profile = new Profile(nullptr, loggedUser);
    profile->show();
}

void ChatWindow::connectToHost(const QString &ip, const QString &port, const QString &user)
{
    _socket.connectToHost(ip, port.toUInt());
}

void ChatWindow::sendMessage(const QString &message)
{


    _socket.write(message.toUtf8());
    ui->listWidgetMessages->addItem(loggedUser + " -> " );
    _socket.flush();
}

void ChatWindow::onConnected()
{
    qInfo() << "Connected to host";
}

void ChatWindow::onErrorOccurred(QAbstractSocket::SocketError error)
{
    qWarning() << "Error:" << error;
}

void ChatWindow::onReadyRead()
{
    const auto message = _socket.readAll();
    emit newMessage(message);


            ui->listWidgetMessages->addItem(message);


//    ui->listWidgetMessages->addItem(message);
//    qInfo() << message;
}

void ChatWindow::on_btnViewChatHistory_clicked()
{

  //  showChatHistory();

 //   showHistory();

    jsonTest();


}




void ChatWindow::on_btnChatRooms_clicked()
{
    hide();
    ChatRooms *chtRooms = new ChatRooms();
    chtRooms->show();
}

void ChatWindow::clearJsonObject(QJsonObject &object)
{
    QStringList strList = object.keys();
    for(int i = 0; i < strList.size(); ++i)
    {
        object.remove(strList.at(i));
    }
}


void ChatWindow::on_btnSaveChatHistory_clicked()
{

    QJsonArray jsonArray;
    QJsonObject rootObject;
    QJsonObject branchObject;
    QJsonObject leafObject;
    leafObject.insert("quality", 18.2);
    leafObject.insert("temp", 25.0);
    branchObject.insert("I1", leafObject);
    jsonArray.append(branchObject);
    clearJsonObject(leafObject);
    clearJsonObject(branchObject);

    leafObject.insert("quality", 2000);
    leafObject.insert("temp", 20.0);
    branchObject.insert("I2", leafObject);
    jsonArray.append(branchObject);
    clearJsonObject(leafObject);
    clearJsonObject(branchObject);

    leafObject.insert("value", 98);
    branchObject.insert("RO Rejection", leafObject);
    jsonArray.append(branchObject);
    clearJsonObject(leafObject);
    clearJsonObject(branchObject);

    leafObject.insert("value", 3);
    branchObject.insert("TOC", leafObject);
    jsonArray.append(branchObject);
    clearJsonObject(leafObject);
    clearJsonObject(branchObject);

    rootObject.insert("heartData", jsonArray);
    QJsonDocument jsonDocument;
    jsonDocument.setObject(rootObject);
    QByteArray byteArray = jsonDocument.toJson(QJsonDocument::Indented);
    QFile file;
    file.setFileName(filePath + "Chats.json");
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {

        return;
    }
    QTextStream out(&file);
    out << byteArray;
    file.close();

}



void ChatWindow::showContacts()
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
                   ui->listWidgetContacts->addItem(chatContact);
            }
}

void ChatWindow::showGroups()
{
    QString val;
    QString chatGroup;

          QFile file;
          file.setFileName(filePath + "Groups.json");
          file.open(QIODevice::ReadOnly | QIODevice::Text);
          val = file.readAll();
          file.close();
          QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
          QJsonObject rootObj = d.object();
          QJsonArray ptsArray = rootObj.value("ChatRooms").toArray();

          foreach(const QJsonValue & val, ptsArray){
                  chatGroup=val.toObject().value("RoomName").toString();
                   ui->listWidgetGroups->addItem(chatGroup);

            }
}


void ChatWindow::showOnlineUsers()
{

    QString val;
    QString onlineUser;

          QFile file;
          file.setFileName(filePath + "login.json");
          file.open(QIODevice::ReadOnly | QIODevice::Text);
          val = file.readAll();
          file.close();
          QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
          QJsonObject rootObj = d.object();
          QJsonArray ptsArray = rootObj.value("users").toArray();

          foreach(const QJsonValue & val, ptsArray){
                  onlineUser=val.toObject().value("UserName").toString();
                  const auto obj = val.toObject();
                  if (obj["Online"] == "True") {
//                       ui->listWidgetOnline->addItem(onlineUser);
                  }

            }
//          ui->listWidgetOnline->addItem("Pabasara");  // issallama meeka run wenawa, passene
          // group chat ekata sashi eka open karanne, eeka open karanna kalin meeka comment karala
          // pahala 2ka uncomment karanna, sashi eke witarak refresh button eka obanna iitapsse

        ui->listWidgetOnline->addItem("Shashi"); // shashi eken log unata psse sashi eke me 2ka uncomment karanna
       ui->listWidgetOnline->addItem("Pabasara");

}

void ChatWindow::showChatHistory()
{
    QString val;
    QString chatHistory;

          QFile file;
          file.setFileName(filePath + "Chats.json");
          file.open(QIODevice::ReadOnly | QIODevice::Text);
          val = file.readAll();
          file.close();
          QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
          QJsonObject rootObj = d.object();
          QJsonArray ptsArray = rootObj.value("chatHistory").toArray();

          qWarning() << tr("QJsonObject[appName] of value: ") << rootObj["messages"];
          QJsonArray test = rootObj["messages"].toArray();
          qWarning() << test[1].toString();

          ui->listWidgetMessages->addItem(test[1].toString());


          foreach(const QJsonValue & val, ptsArray){
                  chatHistory=val.toObject().value("UserName").toString();

                  ui->listWidgetMessages->addItem(chatHistory);

                  QJsonArray ptsArray = rootObj.value("chats").toArray();



//                  foreach(const QJsonValue & val, ptsArray){
//                          chatHistory=val.toObject().value("messages").toString();
//        //                   qWarning() << jUserName;


//                           ui->listWidgetMessages->addItem(chatHistory);
//                         //  ui->lblUserName->setText(onlineUser);

//                    }
//                   ui->listWidgetMessages->addItem(chatHistory);
                 //  ui->lblUserName->setText(onlineUser);

            }





}

void ChatWindow::showHistory()
{
        QString val;
              QFile file;
              file.setFileName(filePath + "Chats.json");
              file.open(QIODevice::ReadOnly | QIODevice::Text);
              val = file.readAll();
              file.close();
              qWarning() << val;
              QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
              QJsonObject sett2 = d.object();
              QJsonValue value = sett2.value(QString("chatHistory"));
              qWarning() << value;
              QJsonObject item = value.toObject();
//              qWarning() << tr("QJsonObject of description: ") << item;

//              qWarning() << tr("QJsonObject[users] of value: ") << item["messages"];
              QJsonArray test = item["messages"].toArray();
              qWarning() << test[1].toString();
              ui->listWidgetMessages->addItem(item["messages"].toString());
}

void ChatWindow::jsonTest()
{

    QString val;
          QFile file;
          file.setFileName(filePath + "Chats.json");
          file.open(QIODevice::ReadOnly | QIODevice::Text);
          val = file.readAll();
          file.close();


    QByteArray jsonData = val.toUtf8();
    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonData);

    QJsonObject object = jsonDocument.object();
    QJsonArray contactsArray = object.value("groups").toArray();

    foreach (const QJsonValue & value, contactsArray) {
        QJsonObject obj = value.toObject();
        if(obj["users"].toString().contains(loggedUser))
        {
            groupChats.append(obj["groupName"].toString());
            groupChatUsers.append(obj["users"].toString());

        }

    }

    foreach (const QString & value, groupChats) {
        ui->listWidgetMessages->addItem(value);
//        qWarning() << "test groupChatsList " + value;
        foreach (const QString & value, groupChatUsers) {
            ui->listWidgetMessages->addItem(value);
//            qWarning() << "test groupChatUsers " + value;

     }
  }
}

void ChatWindow::on_sendButton_clicked()
{
    sendMessage(ui->txtMessage->text());
    ui->txtMessage->clear();
}

void ChatWindow::on_btnSignOut_clicked()
{
    hide();
    Login *login = new Login();
    login->show();
}

void ChatWindow::on_btnRefersh_clicked()
{
    showOnlineUsers();
}

void ChatWindow::on_btnRefershRooms_clicked()
{
    showGroups();
}


void ChatWindow::on_listWidgetOnline_itemDoubleClicked(QListWidgetItem *item)
{
    item->setBackgroundColor(QColor(128,128,255));
}


void ChatWindow::on_listWidgetGroups_itemDoubleClicked(QListWidgetItem *item)
{
    QMessageBox chatDialogMsg;
      chatDialogMsg.setText("Do you want to chat with ? \n Rumesh \n Pabasara \n Shashi \n so please make sure to open their window");
      chatDialogMsg.setStandardButtons (QMessageBox::No | QMessageBox::Yes);
       if(chatDialogMsg.exec() == QMessageBox::Yes)
       {
           QString GroupName = ui->listWidgetGroups->currentItem()->text();
           ui->lblGroupName->setText(GroupName);
           ui->lblGroupHeader->setText("Group Chat");
       }
      else
       {
       }

}

