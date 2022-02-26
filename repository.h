#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QString>
#include <QMap>


class profile;
class Repository
{
    QSqlDatabase db;
    bool connectDB();
    bool conDB;
public:
    Repository();
    ~Repository();

    bool SaveProfile(const QString &name,
                     const QString &login,
                     const QString &password,
                     const QString &firstName,
                     const QString &lastName);
    QMap<QString, QString> GetProfile();
    bool UniquenessOfLogin(const QString &login);
};

#endif // REPOSITORY_H
