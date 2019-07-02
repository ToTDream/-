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
    void reshow();
signals:
    void call_studentmanage(int, QString, int);
    void call_teachermanage(int, QString, QString);
private slots:
    void on_login_clicked();
    void on_exit_clicked();
    void on_id_textChanged(const QString &arg1);
private:
    Ui::LoginDialog *ui;
    QButtonGroup *radiogroup;
    int judgePw(int, QString);
    void readPassword();
};

#endif // LOGINDIALOG_H
