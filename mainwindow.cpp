#include "mainwindow.h"

#include "ui_mainwindow.h"
#include <QTabBar>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <string>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket=new QTcpSocket(this);
    ui->tabWidget->tabBar()->hide();
    ui->tabWidget_2->tabBar()->hide();
    ui->tabWidget_2->setCurrentIndex(0);
    connect(socket, SIGNAL(readyRead()), this, SLOT(sockReady()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(sockDisc()));
    //ui->search->textChanged()
    //this->ui->search->textChanged->connect(Search());
    socket->connectToHost("127.0.0.1",5555);
    profile=new Profile();
    ReadDate();
    SetProfile();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ReadDate()
{
    profile->GetProfile();
}

void MainWindow::SetProfile()
{
    QJsonObject msg{
      {"code",      "profile"},
      {"nick",      profile->GetNickName()},
      {"login",     profile->GetLogin()},
      {"password",  profile->GetPassword()},
      {"firstName", profile->GetFirstName()},
      {"lastName",  profile->GetLastName()}
    };

    auto data=json.JsonInByteArr(msg);
    socket->write(data);
}

void MainWindow::sockReady()
{
    if (socket->waitForConnected(500))
    {
        socket->waitForReadyRead(500);
        msg=new QString;
        *msg=socket->readAll();
        json.Read(*msg);

        if(!con)
        {
            ClientId= json.Key("id").toInt();
            ui->lineEdit->setText(json.Key("msg").toString());
            qDebug()<<json.Key("msg").toString();
            con=true;
        }
        else
        {
            ui->textEdit_2->append(json.Key("msg").toString());
        }


    }
}

void MainWindow::sockDisc()
{
    //qDebug()<<"Disconnect";
    socket->deleteLater();
}


void MainWindow::on_pushButton_clicked()
{
    if(!con)
    {
        socket->connectToHost("127.0.0.1",5555);

        ui->pushButton->setText("Disconnect");
    }
}


void MainWindow::on_textEdit_windowTitleChanged(const QString &title)
{
    msg=new QString;
    *msg=title;
}


void MainWindow::on_pushButton_2_clicked()
{
    msg=new QString;
    *msg=ui->textEdit->toPlainText();


    QJsonObject msgClient{
      {"code",              "msgForPerson"},
      {"id",                ClientId},
      {"secondID",          ui->tabWidget->tabText(1)},
      {"recipientLogin",    ClientId},
      {"msg",               msg->toStdString().c_str()},
    };

    auto Data=json.JsonInByteArr(msgClient);
    socket->write(Data);

    ui->textEdit->clear();
}


void MainWindow::on_profile_triggered()
{
    ui->tabWidget_2->setCurrentIndex(1);
}


void MainWindow::on_Save_clicked()
{


}

void MainWindow::Search()
{

}


void MainWindow::on_Person_1_clicked()
{
    ui->tabWidget->setCurrentIndex(1);
    ui->pushButton_3->setText("Person_1");
}


void MainWindow::on_pushButton_4_clicked()
{
    ui->tabWidget_2->setCurrentIndex(0);
}

