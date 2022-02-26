#ifndef JSONHELPER_H
#define JSONHELPER_H
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <typeinfo>
#include <QByteArray>

class JSONhelper : public QJsonValue
{

    QJsonDocument jsonResponse;
    QJsonArray jsonArray;
    QJsonObject jsonObject;

public:
    JSONhelper();

    QJsonObject Read(const QString str);
    QJsonValue Key(const QString key);
    QJsonValue ReadByKey(const QString str, const QString key);
    QByteArray JsonInByteArr(const QJsonObject &obj);



};

#endif // JSONHELPER_H
