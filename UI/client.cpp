#include <QDir>
#include <QFile>
#include <QDebug>
#include "client.h"
#include "changepw.h"
#include <QMessageBox>
#include "ui_client.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "studentmanage.h"
#include "teachermanage.h"

client::client(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::client)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowIcon(QIcon(":/image/main.jpg"));
    setWindowTitle(tr("教务管理系统"));
    start();                         //初始化
    login = new LoginDialog();      //新建登录窗口
    login -> show();
    host = nullptr;
    connect(login, SIGNAL(post_host_id(int)), this, SLOT(setId(int)));
    connect(login, SIGNAL(Login(QString, QString)), this, SLOT(Login(QString, QString)));
    connect(login, SIGNAL(call_studentmanage(int)), this, SLOT(create_studentmanage(int)));
    connect(login,SIGNAL(call_teachermanage(int)), this, SLOT(create_teachermanage(int)));
    ui -> setupUi(this);
    setMinimumSize(640, 470);
    setMaximumSize(640, 470);
    setFocusPolicy(Qt::StrongFocus);
}
void client::Login(QString _id, QString _pw)
{
    qDebug() << "Login";
    blockSize = 0; //初始化其为0
    tcpsocket->connectToHost(QHostAddress::LocalHost, 6666);
    connect(tcpsocket, SIGNAL(readyRead()),this, SLOT(readData()));
    sendData("2 " + _id + " " + _pw);
}
void client::setId(int _id)
{
    id = _id;
}

void client::readData()
{
    QDataStream in(tcpsocket);

    in.setVersion(QDataStream::Qt_4_6);
    //设置数据流版本，这里要和服务器端相同
    blockSize =  tcpsocket -> read(2).toInt();
    QString info;
    in >> info;
    qDebug() << "client read" << info;
    if(info.isEmpty())return;
    QStringList list = info.split(' ');
    switch(list[1].toInt())
    {
        case CheckPwAns: Judge(list[2]); break;
        case CourseOfTeacher: host -> updatewidget(list, false, " "); break;
        case StudentOfCourse: host -> updatewidget(list, true, list[2]); break;
        case SelectCourse: host -> updatewidget(list, true); break;
        case OptionalCourse: host -> updatewidget(list, false); break;
        case AllCourse: host -> showAllWidget -> update(list); break;
        case DetailOfStudent: host -> showdetail(list); break;
    }
}
void client::Judge(QString ans)
{
    if(ans != '1'){sendData("12");tcpsocket ->abort();}
    login -> judgePw(ans);
}
void client::sendData(QString msg)
{
    qDebug() << "client send -- " << msg;
    QByteArray block;
    QDataStream out(&block,QIODevice::WriteOnly);

    //设置数据流的版本，客户端和服务器端使用的版本要相同
    out.setVersion(QDataStream::Qt_4_6);

    out << (quint16) 0;
    out << QString::number(id) + " " + msg;
    out.device() -> seek(0);
    out << (quint16) (block.size() - sizeof(quint16));
    if(!tcpsocket)qDebug() << "empty";
    tcpsocket -> write(block);
}

//创建动作
void client::createAction()
{
    logoutAct = new QAction(QIcon(":/images/logout.jpg"), tr("注销"), this);
    logoutAct->setToolTip ("注销");
    logoutAct->setStatusTip ("注销账号");
    connect(logoutAct, SIGNAL(triggered(bool)), this, SLOT(logout()));

    changepwAct = new QAction(QIcon(":/images/changePw.jpg"), tr("修改密码"), this);
    changepwAct->setToolTip ("修改密码");
    changepwAct->setStatusTip ("修改密码");
    connect(changepwAct, SIGNAL(triggered(bool)), this, SLOT(changePw()));

    exitAct = new QAction(QIcon(":/images/exit.jpg"), tr("退出"), this);
    exitAct->setToolTip ("退出");
    exitAct->setStatusTip ("退出");
    connect(exitAct, SIGNAL(triggered(bool)), this, SLOT(exit()));

    showallAct = new QAction(QIcon(":/images/showall.jpg"), tr("所有课程"), this);
    showallAct->setToolTip ("显示所有课程");
    showallAct->setStatusTip ("显示所有课程");

    multi_user = new QAction(QIcon(":/images/multi-user.jpg"), tr("添加用户"), this);
    multi_user->setToolTip ("添加用户");
    multi_user->setStatusTip ("添加用户");
    connect(multi_user, SIGNAL(triggered(bool)), this, SLOT(add_user()));
}
void client::add_user()
{
    emit post_add_user();
}
//退出
void client::exit()
{
    close();
}

//初始化
void client::start()
{
    id = 0;
    tcpsocket = new QTcpSocket(this);
    createAction();
    createMenu();
    createToolBars();
    createStatusBar();
}

//创建工具栏
void client::createToolBars()
{
    centreToolBar = addToolBar(tr("系统"));
    centreToolBar -> addAction(multi_user);
    centreToolBar -> addAction(logoutAct);
    centreToolBar -> addAction(exitAct);
    centreToolBar -> addSeparator();

    personToolBar = addToolBar(tr("个人"));
    personToolBar -> addAction(changepwAct);
    personToolBar -> addSeparator();

    courseToolBar = addToolBar(tr("课程管理"));
    courseToolBar -> addAction(showallAct);
}

//创建菜单栏
void client::createMenu()
{
    menuBar() -> clear();

    centreMenu = menuBar() -> addMenu(tr("系统"));
    centreMenu -> addAction(multi_user);
    centreMenu -> addAction(logoutAct);
    centreMenu -> addAction(exitAct);
    centreMenu -> addSeparator();

    personMenu = menuBar() -> addMenu(tr("个人中心"));
    personMenu -> addAction(changepwAct);
    personMenu -> addSeparator();

    courseMenu = menuBar() -> addMenu(tr("课程管理"));
    courseMenu -> addAction(showallAct);
    courseMenu -> addSeparator();
}

//状态栏
void client::createStatusBar()
{
    statusBar() -> showMessage(tr("登录成功"), 2000);
}

//注销
void client::logout()
{
    QMessageBox::StandardButton reply= QMessageBox::question(this, "注意", "确认注销账号?", QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::No)return;
    sendData(tr("12"));
    QMessageBox::information(this, "通知", "已注销", Qt::NoButton);
    tcpsocket -> abort();
    delete host; host = nullptr;
    hide();                             //隐藏主窗口
    login -> reshow();                  //显示登录框
}

//修改密码
void client::changePw()
{
//    弹出密码修改窗口
    changepw *dialog = new changepw();
    dialog -> show();
    connect(dialog, SIGNAL(post_pw(QString)), this, SLOT(changePw(QString)));
    connect(dialog, SIGNAL(cancel()), this, SLOT(show()));
}

void client::changePw(QString newpw)
{
    sendData("1 " + newpw);
    show();
    statusBar() -> showMessage(tr("修改密码成功"), 2000);
}

//创建学生端
void client::create_studentmanage(int _id)
{
    id = _id;
    host = new studentmanage(_id, ui -> centralwidget);
    connect(host, SIGNAL(MsendData(QString)), this, SLOT(sendData(QString)));
    connect(showallAct, SIGNAL(triggered(bool)), host, SLOT(showAllCourse()));
    sendData("10");
    show();
}

//创建教师端
void client::create_teachermanage(int _id)
{
    id = _id;
    host = new teachermanage(_id, ui -> centralwidget);
    connect(host, SIGNAL(MsendData(QString)), this, SLOT(sendData(QString)));
    connect(showallAct, SIGNAL(triggered(bool)), host, SLOT(showAllCourse()));
    sendData("5");
    show();
}

//关闭窗口
void client::closeEvent(QCloseEvent * event)
{
    if(QMessageBox::question(this, "Title", "确认退出管理系统吗??", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)  
    {
        sendData("12");
        QMessageBox::information(this, "通知", "成功退出", Qt::NoButton);
        event -> accept();
    }
    else event->ignore();
}

client::~client()
{
    delete multi_user;
    delete exitAct;
    delete logoutAct;qDebug() << "delete client1";
    delete changepwAct;
    delete showallAct;
    delete login;
    delete ui;
}

