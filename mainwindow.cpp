#include <QFile>
#include <QDebug>
#include "changepw.h"
#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "studentmanage.h"
#include "teachermanage.h"
#include <QDir>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setWindowIcon(QIcon(":/image/main.jpg"));
    setWindowTitle(tr("教务管理系统"));
    start();                            //初始化
    login = new LoginDialog(this);      //新建登录窗口
    Manage = nullptr;
    connect(login, SIGNAL(call_studentmanage(int)), this, SLOT(create_studentmanage(int)));
    connect(login,SIGNAL(call_teachermanage(int)), this, SLOT(create_teachermanage(int)));
    login -> show();
    ui -> setupUi(this);
    setMinimumSize(640, 470);
    setMaximumSize(640, 470);
    setFocusPolicy(Qt::StrongFocus);
}
//创建动作
void MainWindow::createAction()
{
    logoutAct = new QAction(QIcon(":/image/logout.jpg"), tr("注销"), this);
    logoutAct->setToolTip ("注销");
    logoutAct->setStatusTip ("注销账号");
    connect(logoutAct, SIGNAL(triggered(bool)), this, SLOT(logout()));

    changepwAct = new QAction(QIcon(":/image/changePw.jpg"), tr("修改密码"), this);
    changepwAct->setToolTip ("修改密码");
    changepwAct->setStatusTip ("修改密码");
    connect(changepwAct, SIGNAL(triggered(bool)), this, SLOT(changePw()));

    exitAct = new QAction(QIcon(":/image/exit.jpg"), tr("退出"), this);
    exitAct->setToolTip ("退出");
    exitAct->setStatusTip ("退出");
    connect(exitAct, SIGNAL(triggered(bool)), this, SLOT(exit()));

    showallAct = new QAction(QIcon(":/image/showall.jpg"), tr("所有课程"), this);
    showallAct->setToolTip ("显示所有课程");
    showallAct->setStatusTip ("显示所有课程");
}
//退出
void MainWindow::exit()
{
    close();
}
//初始化
void MainWindow::start()
{
    createAction();
    createMenu();
    createToolBars();
    createStatusBar();
}
//创建工具栏
void MainWindow::createToolBars()
{
    centreToolBar = addToolBar(tr("系统"));
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
void MainWindow::createMenu()
{
    menuBar() -> clear();

    centreMenu = menuBar() -> addMenu(tr("系统"));
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
void MainWindow::createStatusBar()
{
    statusBar() -> showMessage(tr("登录成功"), 2000);
}
//注销
void MainWindow::logout()
{
    qDebug() << "logout";
    QMessageBox::StandardButton reply= QMessageBox::question(this, "注意", "确认注销账号?", QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::No)return;

    Manage -> write();                  //更新信息
    delete Manage;
    Manage = nullptr;
    statusBar() -> showMessage(tr("正在注销..."), 1000);
    hide();                             //隐藏主窗口
    login -> reshow();                  //显示登录框
}
//修改密码
void MainWindow::changePw()
{
//    弹出密码修改窗口
    changepw *dialog = new changepw();
    dialog -> show();
    connect(dialog, SIGNAL(post_pw(QString)), this, SLOT(changePw(QString)));
    connect(dialog, SIGNAL(cancel()), this, SLOT(show()));
}
void MainWindow::changePw(QString newpw)
{
    login -> password[Manage -> one -> get_id()] = newpw;
    show();
    statusBar() -> showMessage(tr("修改密码成功"), 2000);
}
//创建学生端
void MainWindow::create_studentmanage(int _id)
{
    Manage = new studentmanage(_id, ui -> centralWidget);
    connect(showallAct, SIGNAL(triggered(bool)), Manage, SLOT(showAllCourse()));
    show();
}
//创建教师端
void MainWindow::create_teachermanage(int _id)
{
    Manage = new teachermanage(_id, ui -> centralWidget);
    connect(showallAct, SIGNAL(triggered(bool)), Manage, SLOT(showAllCourse()));
    show();
}
//关闭窗口
void MainWindow::closeEvent(QCloseEvent * event)
{
    if(QMessageBox::question(this, "Title", "确认退出管理系统吗??", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
         event->accept();
    else event->ignore();
}
MainWindow::~MainWindow()
{
    delete centreMenu;
    delete personMenu;
    delete courseMenu;
    delete centreToolBar;
    delete personToolBar;
    delete courseToolBar;
    delete exitAct;
    delete logoutAct;
    delete changepwAct;
    delete showallAct;
    delete login;
    delete ui;
}
