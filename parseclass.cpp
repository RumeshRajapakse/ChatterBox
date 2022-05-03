#include "parseclass.h"

ParseClass::ParseClass(QObject *parent)
    : QObject{parent}
{

}


void ParseClass::clearJsonObject(QJsonObject &object)
{
    QStringList strList = object.keys();
    for(int i = 0; i < strList.size(); ++i)
    {
        object.remove(strList.at(i));
    }
}

void ParseClass::createJsonFile(const QString &fileName)
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
    QFile file(fileName);
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


void ParseClass::parseJsonFile(const QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << QString("fail to open the file: %1, %2, %3").arg(__FILE__).arg(__LINE__).arg(__FUNCTION__);
        return;
    }
    QByteArray array = file.readAll();
    file.close();
    QJsonParseError jsonParseError;
    QJsonDocument jsonDocument(QJsonDocument::fromJson(array, &jsonParseError));
    if(QJsonParseError::NoError != jsonParseError.error)
    {
        qDebug() << QString("JsonParseError: %1").arg(jsonParseError.errorString());
        return;
    }
    QJsonObject rootObject = jsonDocument.object();
    QStringList rootKeys=rootObject.keys();
    qDebug()<<rootKeys<<"\r\n";
    for(auto&rootKey:rootKeys){
        qDebug()<<rootKey<<"\r\n"; //heartData
        QJsonValue rootJsonValue = rootObject.value(rootKey);
        QJsonArray rootJsonArrays = rootJsonValue.toArray();
        for(auto iter = rootJsonArrays.constBegin(); iter != rootJsonArrays.constEnd(); ++iter){
            QJsonObject branchObject = (*iter).toObject(); //I1 Belonging to
            QStringList branchKeys=branchObject.keys();
            for(auto&branchKey:branchKeys){
                qDebug()<<"  "<<branchKey<<"\r\n"; //I1
                QJsonValue leafJsonValue = branchObject.value(branchKey);
                QJsonObject leafObject = leafJsonValue.toObject(); //I1 Belonging to
                QStringList leafKeys=leafObject.keys();
                for(auto&leafKey:leafKeys){
                    double value=leafObject.value(leafKey).toDouble();
                    qDebug()<<"    "<<leafKey<<":"<<value<<"\r\n"; //quality
                }
            }
        }
    }
}


