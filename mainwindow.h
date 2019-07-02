#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <map>
#include <vector>
#include <Qaction>
#include <QString>
#include <QMenuBar>
#include <QToolBar>
#include "manage.h"
#include <QCloseEvent>
#include <QMainWindow>
#include <QApplication>
#include "logindialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:

    Ui::MainWindow *ui;
    QMenuBar *menubar;          //主菜单
    QMenu *centreMenu;          //系统管理菜单
    QMenu *personMenu;          //个人管理菜单
    QMenu *courseMenu;          //课程管理菜单
    QToolBar *centreToolBar;
    QToolBar *personToolBar;
    QToolBar *courseToolBar;    //各动作对应工具栏
//  主窗口动作
    QAction *exitAct;           //退出
    QAction *logoutAct;         //注销
    QAction *changepwAct;       //修改密码
    QAction *showallAct;        //显示所有课程
    LoginDialog *login;         //登录窗口
    manage *Manage;             //管理窗口
    void start();               //初始化
    void createMenu();          //创建菜单
    void createAction();        //创建动作
    void createToolBars();      //创建工具栏
    void createStatusBar();     //创建状态栏
    void closeEvent(QCloseEvent *event);
signals:
private slots:
    void exit();                //退出
    void logout();              //注销
    void changePw();            //修改密码
    void changePw(QString);     //修改密码
    void create_studentmanage(int);//创建学生端
    void create_teachermanage(int);//创建教师端

};

#endif // MAINWINDOW_H
