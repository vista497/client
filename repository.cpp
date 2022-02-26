#include "repository.h"

Repository::Repository()
{
    conDB=connectDB();
    if(!conDB)
    {qDebug()<<"Cannot open database";}
}

Repository::~Repository()
{

    QString connection;
    connection=db.connectionName();
    db.close();
    db=QSqlDatabase();
    db.removeDatabase(connection);
    //db.removeDatabase(QSqlDatabase::defaultConnection);
    qDebug()<<("Disc.....");

}

bool Repository::connectDB()
{
    db = QSqlDatabase::addDatabase("QPSQL");

    db.setHostName("localhost");
    db.setPort(5432);
    db.setDatabaseName("postgres");
    db.setUserName("postgres");
    db.setPassword("postgres");
    if(!db.open())
    {
        qDebug() << "Cannot open database: " << db.lastError();
        return false;
    }
    return true;
}

bool Repository::SaveProfile(const QString &name,const QString &login, const QString &password, const QString &firstName, const QString &lastName)
{


    QSqlQuery query;

    QString db_input = "INSERT INTO client.person (nick_name, login, password, first_name, last_name) VALUES ('%1','%2','%3','%4','%5')";
    db_input=db_input
            .arg(name)
            .arg(login)
            .arg(password)
            .arg(firstName)
            .arg(lastName);

    if(!query.exec(db_input))
    {
        qDebug() << "Repository, method: SaveProfile: Unable to add an entry " << query.lastError();
        return false;
    }

    return true;
}

QMap<QString, QString> Repository::GetProfile()
{
    QMap<QString, QString> res;
    QSqlQuery query;

    QString db_input = "SELECT nick_name, login, password, first_name, last_name FROM client.person WHERE id=1";


    if(!query.exec(db_input))
    {
        qDebug() << "Repository, method: SaveProfile: Unable to add an entry " << query.lastError();
    }

    while (query.next())
    {
        res.insert("nick",query.value(0).toString());
        res.insert("login",query.value(1).toString());
        res.insert("password",query.value(2).toString());
        res.insert("firstName",query.value(3).toString());
        res.insert("lastName",query.value(4).toString());
    }
    return res;
}

bool Repository::UniquenessOfLogin(const QString &login)
{
    QSqlQuery query;

    QString db_input = "SELECT COUNT(*) FROM client.person WHERE login='%1'";
    db_input=db_input.arg(login);

    if(!query.exec(db_input))
    {
        qDebug() << "Repository, method: UniquenessOfLogin: Failed to count " << query.lastError();
    }

    int res=0;
    while (query.next())
    {
        res=query.value(0).toInt();
    }
    if(res!=0){return false;}

    return true;
}


