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
    readPassword();
    setAttribute(Qt::WA_X11DoNotAcceptFocus, true);
    setWindowTitle("登录");
    setParent(parent);
    ui -> setupUi(this);
    QPalette p;
    p.setColor(QPalette::WindowText,Qt::red);
    ui->titlelabel->setPalette(p);
    ui->login->setEnabled(false);

    ui->name->setPlaceholderText("请输入用户名");
    ui->Class->setPlaceholderText("请输入年级（学院）");
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
int LoginDialog::judgePw(int id, QString pw)
{
    if(!password.count(id))return -1;
    if(password[id] != pw)return 0;
    return 1;
}
//读取密码信息
void LoginDialog::readPassword()
{
    password.clear();
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);

    try
    {
        QFile file("D:/QT/C++/student_system(1)/files/password.txt");
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
            throw QString(tr("can't open the file"));

        while(!file.atEnd())
        {
            QByteArray line = file.readLine();
            QString _str(line);
            QStringList list = _str.remove("\n").split(" ");
            password.insert(std::make_pair(list[0].toInt(), list[1]));
        }
    }
    catch(QString e)
    {
        QMessageBox::about(this, "Error!", e);
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

            switch(judgePw(id, ui -> password -> text()))
            {
                case 1:
                        if(!radiogroup->checkedId())//学生登录
                        {
                                QMessageBox::information(this,"通知","恭喜您，登录成功");

                                emit call_studentmanage(ui->id->text().toInt(), ui->name->text(), ui->Class->text().toInt());
                                this->hide();
                        }
                        else//教师登录
                        {
                                QMessageBox::information(this,"通知","恭喜您，登录成功");

                                emit call_teachermanage(ui->id->text().toInt(), ui->name->text(), ui->Class->text());
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
}
