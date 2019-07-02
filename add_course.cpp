#include "add_course.h"
#include "ui_add_course.h"
#include <QMessageBox>
#include <qDebug>
add_course::add_course(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_course)
{
    ui->setupUi(this);
    radiogroup = new QButtonGroup;
    radiogroup->addButton(ui->radioButton, 1);
    radiogroup->addButton(ui->radioButton_2, 0);
}

add_course::~add_course()
{
    delete ui;
    delete radiogroup;
}
//添加课程
void add_course::on_addButton_clicked()
{
    try
    {
        QString strId = ui -> id -> text(), name = ui -> name -> text(), strCredit = ui -> credit -> text();//获取表格数据
        if(strId.isEmpty() || name.isEmpty() || strCredit.isEmpty())            //数据填写不完整
        {
            QMessageBox::information(this, tr("操作失败"), tr("请先填写所有信息"), QMessageBox::Ok);
            ui->credit->setFocus();
            return;
        }
        int id = strId.toInt(), credit = strCredit.toInt();

        if(!id || !credit)throw QString(tr("格式错误。"));                       //填写数据格式出错

        emit addcourse(id, name, credit, radiogroup -> checkedId());            //向管理窗口发送添加课程信号
        this -> close();                                                        //关闭添加课程窗口
    }
    catch(QString e)
    {
        QMessageBox::about(this, "Error", e);
        ui -> credit -> clear();                                                //清除数据
        ui -> credit -> setFocus();                                             //聚焦在需填栏内
    }
}
//重置表单
void add_course::on_resetButton_clicked()
{
    //清除所有填写内容
    ui -> id -> clear();
    ui -> name -> clear();
    ui -> credit -> clear();
    ui -> id -> setFocus();
}
