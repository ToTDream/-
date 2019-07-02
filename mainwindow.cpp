#include <QFile>
#include <QDebug>
#include "changepw.h"
#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "studentmanage.h"
#include "teachermanage.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    start();
    login = new LoginDialog(this);
    Manage = nullptr;
    connect(login, SIGNAL(call_studentmanage(int, QString, int)), this, SLOT(create_studentmanage(int, QString, int)));
    connect(login,SIGNAL(call_teachermanage(int, QString, QString)), this, SLOT(create_teachermanage(int, QString, QString)));
    login -> show();
    ui -> setupUi(this);
    setMinimumSize(640, 470);
    setMaximumSize(640, 470);
    setFocusPolicy(Qt::StrongFocus);
}

void MainWindow::createAction()
{
    logoutAct = new QAction(tr("注销"), this);
    logoutAct->setToolTip ("注销");
    logoutAct->setStatusTip ("注销账号");
    connect(logoutAct, SIGNAL(triggered(bool)), this, SLOT(logout()));

    changepwAct = new QAction(tr("修改密码"), this);
    changepwAct->setToolTip ("修改密码");
    changepwAct->setStatusTip ("修改密码");
    connect(changepwAct, SIGNAL(triggered(bool)), this, SLOT(changePw()));

    exitAct = new QAction(tr("退出"), this);
    exitAct->setToolTip ("退出");
    exitAct->setStatusTip ("退出");
    connect(exitAct, SIGNAL(triggered(bool)), this, SLOT(exit()));

    showallAct = new QAction(tr("所有课程"), this);
    showallAct->setToolTip ("显示所有课程");
    showallAct->setStatusTip ("显示所有课程");
//    connect(showallAct, SIGNAL(triggered(bool)), Manage, SLOT(showAllCourse()));
}
//退出
void MainWindow::exit()
{
    QMessageBox::StandardButton reply= QMessageBox::question(this, "Title", "确认退出管理系统吗??", QMessageBox::Yes | QMessageBox::No);
    if(Manage)Manage -> write();
    if(reply == QMessageBox::Yes) close();
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
    statusBar() -> showMessage(tr("就绪"), 2000);
}
//注销
void MainWindow::logout()
{
    qDebug() << "logout";
    QMessageBox::StandardButton reply= QMessageBox::question(this, "注意", "确认注销账号?", QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::No)return;

    Manage -> write();
    delete Manage;
    Manage = nullptr;
    statusBar() -> showMessage(tr("正在注销..."), 1000);
    hide();
    login -> reshow();
}
//修改密码
void MainWindow::changePw()
{
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
void MainWindow::create_studentmanage(int _id, QString _name, int Class)
{
    Manage = new studentmanage(_id, _name, Class, ui -> centralWidget);
    connect(showallAct, SIGNAL(triggered(bool)), Manage, SLOT(showAllCourse()));
    show();
}
//创建教师端
void MainWindow::create_teachermanage(int _id, QString _name, QString _academy)
{
    Manage = new teachermanage(_id, _name, _academy, ui -> centralWidget);
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
//void MainWindow::reread()
//{
//   Manage -> all_course = all_course;
//   Manage -> all_person = all_person;
//}
MainWindow::~MainWindow()
{
    delete ui;
}
