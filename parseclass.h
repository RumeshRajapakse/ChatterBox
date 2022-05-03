#ifndef PARSECLASS_H
#define PARSECLASS_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QIODevice>
#include <QStringList>
#include <QDebug>
#include <QList>

class ParseClass : public QObject
{
    Q_OBJECT
public:
    explicit ParseClass(QObject *parent = nullptr);
    void clearJsonObject(QJsonObject &object);
    void createJsonFile(const QString &fileName);

    void parseJsonObjectV(QJsonObject &object);
    void parseJsonObjectI(QJsonObject &object);
    void parseJsonObject(QJsonArray::const_iterator iter);
    void parseJsonFile(const QString &fileName);
    void initList();

signals:

};

#endif // PARSECLASS_H
