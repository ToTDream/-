#include <QDebug>
#include <QMessageBox>
#include "logindialog.h"
#include "studentmanage.h"
#include "teachermanage.h"
#include "ui_logindialog.h"
LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    setAttribute(Qt::WA_X11DoNotAcceptFocus, true);
    setWindowTitle("登录");
    setParent(parent);
    ui -> setupUi(this);
    QPalette p;
    p.setColor(QPalette::WindowText,Qt::red);
    ui->titlelabel->setPalette(p);
    ui->login->setEnabled(false);

    ui->id->setPlaceholderText("请输入学号或工号");
    ui->password->setPlaceholderText("请输入密码");
    ui->password->setEchoMode(QLineEdit::Password);

    radiogroup = new QButtonGroup;
    radiogroup->addButton(ui->studentradio, 0);
    radiogroup->addButton(ui->teacherradio, 1);
}

void LoginDialog::reshow()
{
    ui -> password -> clear();
    show();
}
//判断密码信息
void LoginDialog::judgePw(QString cmd)
{
    qDebug() << "judgeans" << cmd;
    switch(cmd.toInt())
    {
        case 1:
                emit post_host_id(ui -> id -> text().toInt());
                if(!radiogroup->checkedId())//学生登录
                {
                        QMessageBox::information(this,"通知","密码正确");

                        emit call_studentmanage(ui->id->text().toInt());
                        this->hide();
                }
                else//教师登录
                {
                        QMessageBox::information(this,"通知","恭喜您，密码正确");

                        emit call_teachermanage(ui->id->text().toInt());
                        this->hide();
                }
                break;
        case -1:
                QMessageBox::warning(this, tr("登录错误"), tr("没有您的账号信息！"), QMessageBox::Ok);
                ui->id->clear();
                ui->id->setFocus();
                break;
        case 0:
                QMessageBox::warning(this, tr("登录错误"), tr("请输入正确的 密码再登录！"), QMessageBox::Ok);
                ui->password->clear();
                ui->password->setFocus();
                break;
     }
}
//登录
void LoginDialog::on_login_clicked()
{
    if(ui->password->text().isEmpty())
    {
        QMessageBox::information(this, tr("请输入密码"), tr("请先输入密码在登录"), QMessageBox::Ok);
        ui->password->setFocus();
    }
    else
    {
        //比较密码
        try
        {
            int id = ui -> id -> text().toInt();
            if(!id)throw QString("学号不符合格式");
            emit Login(ui -> id -> text(), ui -> password -> text());
        }
        catch(QString e)
        {
            QMessageBox::about(this, "Error", e);
        }
    }
}
//退出
void LoginDialog::on_exit_clicked()
{
    QDialog::reject();
}
//激活确认键
void LoginDialog::on_id_textChanged(const QString &arg1)
{
    ui->login->setEnabled(true);
}

LoginDialog::~LoginDialog()
{
    delete ui;
    delete radiogroup;
}
