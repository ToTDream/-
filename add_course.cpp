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
}
//添加课程
void add_course::on_addButton_clicked()
{
    try
    {
        QString strId = ui -> id -> text(), name = ui -> name -> text(), strCredit = ui -> credit -> text();
        if(strId.isEmpty() || name.isEmpty() || strCredit.isEmpty())
        {
            QMessageBox::information(this, tr("操作失败"), tr("请先填写所有信息"), QMessageBox::Ok);
            ui->credit->setFocus();
            return;
        }
        int id = strId.toInt(), credit = strCredit.toInt();

        if(!id || !credit)throw QString(tr("格式错误。"));

        emit addcourse(id, name, credit, radiogroup -> checkedId());
        this -> close();
    }
    catch(QString e)
    {
        QMessageBox::about(this, "Error", e);
        ui -> credit -> clear();
        ui -> credit -> setFocus();
    }
}
//重置填写信息
void add_course::on_resetButton_clicked()
{
    ui -> id -> clear();
    ui -> name -> clear();
    ui -> credit -> clear();
    ui -> id -> setFocus();
}
