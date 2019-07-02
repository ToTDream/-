#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    hide();
    add_User();
}
void MainWindow::add_User()
{
    client* newclient = new client;
    all_client.push_back(newclient);
    connect(newclient, SIGNAL(post_add_user()), this, SLOT(add_User()));
}
MainWindow::~MainWindow()
{
    delete ui;
}
