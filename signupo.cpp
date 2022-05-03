#include "signupo.h"
#include "ui_signup.h"
#include "chatwindow.h"
#include <QFileDialog>
#include <QFileInfo>
#import <QMimeDatabase>
#include "QDebug"
#include <QCryptographicHash>
#include <QJsonObject>
#include "QJsonArray"
#include <QJsonDocument>
#include <QDateTime>

QString loggedinUser;
QString name;
QString imageUrl;
QString email;
QString userName;
QString password;


QString Signup::filePath = "/home/rumesh/Downloads/Latest 1/Latest/CChatterBox/";

Signup::Signup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Signup)
{
    ui->setupUi(this);
}

Signup::~Signup()
{
    delete ui;
}

void Signup::on_btnUploadImage_clicked()
{
    ui->validationError->setText("");
    QString m_fileName = QFileDialog::getOpenFileName(this, "Select an image");
    ui->imageUrl->setText(m_fileName);

    QMimeDatabase db;
    QMimeType mime = db.mimeTypeForFile(m_fileName, QMimeDatabase::MatchContent);
    QString fileType = mime.preferredSuffix().toLower();

    if(fileType == "jpg" || fileType == "jpeg" || fileType == "png")
    {
        QGraphicsScene *scene =  new QGraphicsScene;
        QPixmap pixmap(m_fileName);
        scene->addPixmap(pixmap);
        ui->graphicsView->setScene(scene);
        ui->graphicsView->fitInView(scene->sceneRect(),Qt::KeepAspectRatio);
        ui->graphicsView->show();

    }
    else
    {
        ui->validationError->setText("Invalid file type");
    }
}


void Signup::on_btnSignUp_clicked()
{
    if(ui->validationError->text() != "")
    {
        ui->validationError->setText(ui->validationError->text() + ".You cannot save invalid details");
        return;
    }

    name = ui->txtUsername->toPlainText();
    imageUrl = ui->imageUrl->text();
    email = ui->txtEmail->toPlainText();

//    QString jsonFilePath = loggedinUser+".json";

//    QFile inFile(jsonFilePath);
//    inFile.open(QIODevice::ReadOnly|QIODevice::Text);
//    QString data = inFile.readAll();
//    inFile.close();
//    QByteArray jsonData = data.toUtf8();
//    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonData);

//    // write to json file
//    QJsonObject configDetails;
//    configDetails.insert( "image", imageUrl );
//    configDetails.insert( "name", name);
//    configDetails.insert("password", password);
//    configDetails.insert("email", email);
//    configDetails.insert("userName", userName);
//    jsonDocument.setObject(configDetails);
//    inFile.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
//    inFile.write(jsonDocument.toJson());
//    inFile.close();

//    this->close();
//    ChatDashboard cdb;
//    cdb.setModal(true);
//    cdb.exec();


    addLogs(name ,email);


}

void Signup::saveProfileJson()
{

//    QFile file(filePath + "test.json" );
//    file.open(QIODevice::ReadOnly | QIODevice::Text | QIODevice::Append);
//    QJsonParseError JsonParseError;
//    QJsonDocument JsonDocument = QJsonDocument::fromJson(file.readAll(), &JsonParseError);
//    file.close();
//    QJsonObject RootObject = JsonDocument.object();
//    QJsonValueRef ref = RootObject.find("Address").value();
//    QJsonObject m_addvalue = ref.toObject();
//    m_addvalue.insert("Street","India");//set the value you want to modify
//    ref=m_addvalue; //assign the modified object to reference
//    JsonDocument.setObject(RootObject); // set to json document
//    file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
//    file.write(JsonDocument.toJson());
//    file.close();


}

bool Signup::addLogs(QString flightType, QString flightTextLogs){

    QFile file(filePath + "profiles.json"); // json file
        if( !file.open( QIODevice::ReadOnly | QIODevice::Append ) ) //read json content
        {
            //open file error ...
            return false;
        }

        QJsonDocument jsonOrg = QJsonDocument::fromJson( file.readAll() );
        file.close();

        //local variable, do not use m_ prefix.
        QJsonObject projectDetails = { {"Type", flightType},
                                       {"TextLog", flightTextLogs},
                                       {"Date and Time", QDateTime::currentDateTime().toString( "yyyy-MM-dd hh:mm:ss" )} };

        QJsonObject notificationObj =  {{ "Notifications", projectDetails }};

        QJsonArray arrLog = jsonOrg.array();
        arrLog.push_back( notificationObj );

        QJsonDocument doc( arrLog );

        if( !file.open( QIODevice::WriteOnly | QIODevice::Append) ) //write json content to file.
        {
            //cannot open for write ...
            return false;
        }

        file.write(doc.toJson());
        file.close();

        return true;
}
