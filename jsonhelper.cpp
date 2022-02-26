#include "jsonhelper.h"

JSONhelper::JSONhelper()
{

}

QJsonObject JSONhelper::Read(const QString str)
{
    jsonResponse = QJsonDocument::fromJson(str.toLatin1());
    jsonArray = jsonResponse.array();
    jsonObject = jsonArray.first().toObject();
    return jsonObject;
}

QJsonValue JSONhelper::Key(const QString key)
{
    return jsonObject.value(key);
}

QJsonValue JSONhelper::ReadByKey(const QString str, const QString key)
{
    jsonResponse = QJsonDocument::fromJson(str.toLatin1());
    jsonArray = jsonResponse.array();
    jsonObject = jsonArray.first().toObject();
    return jsonObject.value(key);
}

QByteArray JSONhelper::JsonInByteArr(const QJsonObject &obj)
{
    QJsonArray jsarray {obj};
    QJsonDocument jsDoc(jsarray);

    return QString::fromLatin1(jsDoc.toJson()).toLatin1();
}


