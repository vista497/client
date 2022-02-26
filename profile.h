#ifndef PROFILE_H
#define PROFILE_H

#include <QWidget>
#include <repository.h>
#include <QMessageBox>
namespace Ui {
class Profile;
}

class Profile : public QWidget
{
    Q_OBJECT
    QString name;
    QString login;
    QString password;
    QString firstName;
    QString lastName;
    Repository *connection;

public:
    explicit Profile(QWidget *parent = nullptr);
    ~Profile();

    void initProfile( QString name,
                      QString login,
                      QString password="",
                      QString firstName="",
                      QString lastName="");
    bool SaveProfile();
    void GetProfile();

    QString GetLogin();
    QString GetNickName();
    QString GetPassword();
    QString GetFirstName();
    QString GetLastName();

private slots:
    void on_saveBtn_clicked();

private:
    Ui::Profile *ui;
};

#endif // PROFILE_H
