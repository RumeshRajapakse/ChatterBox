#include "profile.h"
#include "ui_profile.h"
#include "QFile"
#include "QJsonDocument"
#include "QJsonObject"
#include "QDebug"
#include "QJsonArray"
#include "QString"
#include "QMessageBox"
#include "chatwindow.h"

QString Profile::filePath = "/home/rumesh/Downloads/Latest 1/Latest/CChatterBox/";

Profile::Profile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Profile)
{
    ui->setupUi(this);
}

Profile::~Profile()
{
    delete ui;
}



void Profile::on_btnSaveProfile_clicked()
{
    QString val;
    QString pUserName;
    QString pEmail;
    QString pMobileNumber;
    QString pdateOfBirth;


          QFile file;
          file.setFileName(filePath + "Contacts.json");
          file.open(QIODevice::ReadOnly | QIODevice::Text);
          val = file.readAll();
          file.close();
          qWarning() << val;
          QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
          QJsonObject rootObj = d.object();
       //   QVector<QString> listUsers;
          QJsonArray ptsArray = rootObj.value("contacts").toArray();
//          QJsonValue value = rootObj.value(QString("UserName"));
//          qWarning() << value;
//          QJsonObject item = value.toObject();

          foreach(const QJsonValue & val, ptsArray){
                  pUserName=val.toObject().value("UserName").toString();
                  pEmail=val.toObject().value("Password").toString();
                  pMobileNumber=val.toObject().value("UserName").toString();
                  pdateOfBirth=val.toObject().value("Password").toString();
                   qWarning() << pUserName;
                   qWarning() << pEmail;
                   qWarning() << pMobileNumber;
                   qWarning() << pdateOfBirth;

            }

                 ui->txtProfileUsername->setText(pUserName);
                 ui->txtProfileEmail->setText(pEmail);
                 ui->txtProfilePhoneNo->setText(pMobileNumber);
                 ui->txtProfileDOB->setText(pdateOfBirth);
}


void Profile::on_btnExit_clicked()
{
    hide();
    ChatWindow *chatWindow = new ChatWindow();
    chatWindow->show();
}

