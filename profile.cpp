#include "profile.h"
#include "ui_profile.h"

Profile::Profile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Profile)
{
    ui->setupUi(this);

}

Profile::~Profile()
{
    delete ui;
}

void Profile::initProfile(QString name, QString login, QString password, QString firstName, QString lastName)
{
    this->name=name;
    this->login=login;
    this->password=password;
    this->firstName=firstName;
    this->lastName=lastName;
}

bool Profile::SaveProfile()
{
    connection=new Repository;
    auto a=connection->UniquenessOfLogin(this->login);
    if(!connection || !connection->UniquenessOfLogin(this->login))
    {
        return false;
    }

    connection->SaveProfile(name, login, password, firstName, lastName);
    return true;
}

void Profile::GetProfile()
{
    connection=new Repository();

    QMap res = connection->GetProfile();
    if(res.size()==0)
    {
        this->name="";
        this->login="";
        this->password="";
        this->firstName="";
        this->lastName="";
    }
    else
    {
        this->login=res["login"];
        this->name=res["nick"];
        this->password=res[ "password"];
        this->firstName=res["firstName"];
        this->lastName=res["lastName"];
    }
}



QString Profile::GetLogin() { return login; }
QString Profile::GetPassword() { return password; }
QString Profile::GetFirstName() { return firstName; }
QString Profile::GetLastName() { return lastName; }
QString Profile::GetNickName() { return name; }

void Profile::on_saveBtn_clicked()
{
//    *name=ui->nickname->toPlainText();
//    *login=ui->login->toPlainText();
    initProfile(ui->nickname->toPlainText(),
                ui->login->toPlainText(),
                ui->password->toPlainText(),
                ui->firstName->toPlainText(),
                ui->lastName->toPlainText());
    if(!SaveProfile())
    {

        QMessageBox msgBox;
        msgBox.setWindowTitle("Внимание");
        msgBox.setText("Логин используется");
        msgBox.exec();
    }

}

