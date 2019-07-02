#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QFile>
#include <QDialog>
#include <QString>
#include "person.h"
#include <QTextCodec>
#include <QButtonGroup>
namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT
public:
    explicit LoginDialog(QWidget *parent = 0);
    std::map<int, QString> password;
    ~LoginDialog();
    void reshow();                                  //登录窗口重现
signals:
    void call_studentmanage(int);                   //学生端调用信号
    void call_teachermanage(int);                   //教师端调用信号
private slots:
    void on_login_clicked();                        //登录按钮点击槽
    void on_exit_clicked();                         //退出按钮点击槽
    void on_id_textChanged(const QString &arg1);    //内容更改槽
private:
    Ui::LoginDialog *ui;
    QButtonGroup *radiogroup;
    int judgePw(int, QString);                      //密码判断
    void readPassword();                            //读取密码数据
    void writePassword();                           //写入（更新）密码数据
};

#endif // LOGINDIALOG_H
