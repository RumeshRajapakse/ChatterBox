#include "chatdashboard.h"
#include "login.h"
#include "profileo.h"
#include "chatrooms.h"
#include "ui_chatdashboard.h"
#include "QFile"
#include "QJsonDocument"
#include "QJsonObject"
#include "QDebug"
#include "QJsonArray"
#include "QThread"
#include "parseclass.h"

QString loggedUser = "User";
QStringList groupChats;
QStringList groupChatUsers;
QStringList groupChatMessages;

QString ChatDashboard::filePath = "/home/rumesh/Downloads/Latest 1/Latest/CChatterBox/";

ChatDashboard::ChatDashboard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChatDashboard)
{
    ui->setupUi(this);
    showContacts();
    showGroups();
    showOnlineUsers();
    connectToHost("127.0.0.1", "8000");
    ui->listWidgetMessages->addItem("Connected to host");
}

ChatDashboard::~ChatDashboard()
{
    delete ui;
}

void ChatDashboard::on_btnEditProfle_clicked()
{
    hide();
    Profile profile;
    profile.setModal(true);
    profile.exec();
}

void ChatDashboard::connectToHost(const QString &ip, const QString &port)
{
    _socket.connectToHost(ip, port.toUInt());
}

void ChatDashboard::sendMessage(const QString &message)
{
    _socket.write(message.toUtf8());
    ui->listWidgetMessages->addItem(loggedUser + " -> " + message);
    _socket.flush();
}

void ChatDashboard::onConnected()
{
    qInfo() << "Connected to host";
}

void ChatDashboard::onErrorOccurred(QAbstractSocket::SocketError error)
{
    qWarning() << "Error:" << error;
}

void ChatDashboard::onReadyRead()
{
    const auto message = _socket.readAll();
    emit newMessage(message);
    ui->listWidgetMessages->addItem("message" + message);
}

void ChatDashboard::on_btnViewChatHistory_clicked()
{

  //  showChatHistory();

 //   showHistory();

    jsonTest();


}




void ChatDashboard::on_btnChatRooms_clicked()
{
    hide();
    ChatRooms chtRooms;
    chtRooms.setModal(true);
    chtRooms.exec();
}

void ChatDashboard::clearJsonObject(QJsonObject &object)
{
    QStringList strList = object.keys();
    for(int i = 0; i < strList.size(); ++i)
    {
        object.remove(strList.at(i));
    }
}


void ChatDashboard::on_btnSaveChatHistory_clicked()
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
    file.setFileName(filePath + "test.json");
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << QString("fail to open the file: %1, %2, %3").arg(__FILE__).arg(__LINE__).arg(__FUNCTION__);
        return;
    }
    QTextStream out(&file);
    out << byteArray;
    file.close();
    qDebug() << byteArray;
}



void ChatDashboard::showContacts()
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
          qDebug() << "There are " << ptsArray.size() << "sets of onlineUsers in the json file";

          foreach(const QJsonValue & val, ptsArray){
                  chatContact=val.toObject().value("UserName").toString();
                   ui->listWidgetContacts->addItem(chatContact);
            }
}

void ChatDashboard::showGroups()
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
          QJsonArray ptsArray = rootObj.value("groups").toArray();
          qDebug() << "There are " << ptsArray.size() << "sets of onlineUsers in the json file";

          foreach(const QJsonValue & val, ptsArray){
                  chatGroup=val.toObject().value("groupName").toString();
                   ui->listWidgetGroups->addItem(chatGroup);

            }
}


void ChatDashboard::showOnlineUsers()
{
    QString val;
    QString onlineUser;

          QFile file;
          file.setFileName(filePath + "Online.json");
          file.open(QIODevice::ReadOnly | QIODevice::Text);
          val = file.readAll();
          file.close();
          QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
          QJsonObject rootObj = d.object();
          QJsonArray ptsArray = rootObj.value("onlineUsers").toArray();
          qDebug() << "There are " << ptsArray.size() << "sets of onlineUsers in the json file";

          foreach(const QJsonValue & val, ptsArray){
                  onlineUser=val.toObject().value("UserName").toString();
                   ui->listWidgetOnline->addItem(onlineUser);
                   ui->lblUserName->setText(onlineUser);

            }
}

void ChatDashboard::showChatHistory()
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
          qDebug() << "There are " << ptsArray.size() << "sets of chatHistory in the json file";

          qWarning() << tr("QJsonObject[appName] of value: ") << rootObj["messages"];
          QJsonArray test = rootObj["messages"].toArray();
          qWarning() << test[1].toString();

          ui->listWidgetMessages->addItem(test[1].toString());


          foreach(const QJsonValue & val, ptsArray){
                  chatHistory=val.toObject().value("UserName").toString();

                  ui->listWidgetMessages->addItem(chatHistory);

                  QJsonArray ptsArray = rootObj.value("chats").toArray();
                  qDebug() << "There are " << ptsArray.size() << "sets of chats in the json file";


            }





}

void ChatDashboard::showHistory()
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
              qWarning() << tr("QJsonObject of description: ") << item;

              qWarning() << tr("QJsonObject[users] of value: ") << item["messages"];
              QJsonArray test = item["messages"].toArray();
              qWarning() << test[1].toString();
              ui->listWidgetMessages->addItem(item["messages"].toString());
}

void ChatDashboard::jsonTest()
{

    QString val;
          QFile file;
          file.setFileName(filePath + "jsonTest.json");
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
        qWarning() << "test groupChatsList " + value;
        foreach (const QString & value, groupChatUsers) {
            ui->listWidgetMessages->addItem(value);
            qWarning() << "test groupChatUsers " + value;


     }
  }
}

void ChatDashboard::on_sendButton_clicked()
{

    sendMessage(ui->txtMessage->text());
    ui->txtMessage->clear();
}


void ChatDashboard::on_btnSignOut_clicked()
{
    hide();
    Login *login = new Login();
    login->show();
}

