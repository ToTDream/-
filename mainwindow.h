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
    QMenuBar *menubar;
    QMenu *centreMenu;
    QMenu *personMenu;
    QMenu *courseMenu;
    QToolBar *centreToolBar;
    QToolBar *personToolBar;
    QToolBar *courseToolBar;
//  主窗口动作
    QAction *exitAct;      //退出
    QAction *logoutAct;    //注销
    QAction *changepwAct;  //修改密码
    QAction *showallAct;
    LoginDialog *login;
    manage *Manage;
    void start();
    void createAction();
    void createMenu();
    void createToolBars();      //创建工具栏
    void createStatusBar();     //创建状态栏
    void readPassword();
    void closeEvent(QCloseEvent *event);
signals:
private slots:
    void exit();
    void logout();
    void changePw();
    void changePw(QString);
    void create_studentmanage(int, QString, int);
    void create_teachermanage(int, QString, QString);

};

#endif // MAINWINDOW_H
