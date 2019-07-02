#include "changepw.h"
#include "ui_changepw.h"
#include <QMessageBox>
changepw::changepw(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::changepw)
{
    ui -> setupUi(this);
    ui -> firstpw -> setEchoMode(QLineEdit::Password);
    ui -> secondpw -> setEchoMode(QLineEdit::Password);
}
//确认键点击
void changepw::on_confirm_clicked()
{
    if(ui -> firstpw -> text() == ui -> secondpw -> text())
    {
        emit post_pw(ui -> firstpw -> text());      //向主窗口发送所更改的密码
        this -> close();                            //关闭本窗口
    }
    else
    {
        QMessageBox::information(this,"错误","密码不一致，请重新输入");
        ui -> secondpw -> clear();                  //清空所填密码
        ui -> secondpw -> setFocus();
    }
}
//重置键点击
void changepw::on_reset_clicked()
{
    ui -> firstpw -> clear();
    ui -> secondpw -> clear();
}
//关闭键点击
void changepw::on_pushButton_clicked()
{
    close();                                        //关闭本窗口
    emit cancel();                                  //发送取消信号
}

changepw::~changepw()
{
    delete ui;
}
