#include "login.h"
#include "ui_login.h"
#include "chatwindow.h"
#include "signupo.h"
#include "QFile"
#include "QJsonDocument"
#include "QJsonObject"
#include "QDebug"
#include "QJsonArray"
#include "QString"
#include "QMessageBox"
#include <QCryptographicHash>


QString Login::filePath = "/home/rumesh/Downloads/Latest 1/Latest/CChatterBox/";

Login::Login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::on_btnLogin_clicked()
{
        QString username = ui->txtUsername->text();
        QString password = ui->txtPassword->text();

        QCryptographicHash hasher(QCryptographicHash::Sha1);
        QByteArray cPassword = password.toUtf8();
        hasher.addData(cPassword);

        if(username.isEmpty())
        {
            QMessageBox::warning(this, "Login", "Username cannot be empty");
        }
        else if(password.isEmpty())
        {
            QMessageBox::warning(this, "Login", "Password cannot be empty");
        }
        else
        {
            QString val;

            QFile file;
            file.setFileName(filePath + "login.json");
            file.open(QIODevice::ReadOnly | QIODevice::Text);
            val = file.readAll();
            file.close();
            QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());

            QJsonObject rootObj = d.object();
            QJsonArray ptsArray = rootObj.value("users").toArray();

            for (const auto entry: ptsArray) {
              const auto obj = entry.toObject();
              if (obj["UserName"] == username) {

                    QString hPassword = obj["Password"].toString();
                    QString dPassword = hasher.result().toHex().toUpper();

                    if(hasher.result().toHex().toUpper() != hPassword)
                    {
                        QMessageBox::warning(this,"Error", "Invalid Password");
                        return;
                    }
                    else if(obj["Password"] == dPassword) {
                        obj["Online"] == "True";
                        file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
                        d.setObject(rootObj);
                        file.write(d.toJson());
                        file.close();



                      hide();
                      ChatWindow *chatWindow = new ChatWindow(nullptr, username);
                      chatWindow->show();
                    break;
                  }
                break;
              }
            }

        }
}

void Login::on_btnGoToSignUp_clicked()
{
    Signup signup;
    signup.setModal(true);
    signup.exec();
}

