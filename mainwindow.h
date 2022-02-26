#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include "profile.h"
#include <iostream>
#include <fstream>
#include <QMessageBox>
#include "jsonhelper.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    //Repository *repo;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int ClientId;
    QString name;
    QString login;
    Profile *profile;
    JSONhelper json;

    QTcpSocket *socket;
    QByteArray *Data;
    QString* msg;
    bool con=false;

    void ReadDate();
    void SetProfile();

public slots:
    void sockReady();
    void sockDisc();

private slots:
    void on_pushButton_clicked();

    void on_textEdit_windowTitleChanged(const QString &title);

    void on_pushButton_2_clicked();

    void on_profile_triggered();

    void on_Save_clicked();
    void Search();

    void on_Person_1_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
