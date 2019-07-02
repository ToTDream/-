#include <qDebug>
#include <QDialog>
#include <QMessageBox>
#include "tea_course.h"
#include "teachermanage.h"
#include "course_student.h"
#include "ui_teachermanage.h"

teachermanage::teachermanage(int _id, QWidget *parent):
    manage(parent),
    ui(new Ui::teachermanage)
{
    ui->setupUi(this);
    setParent(parent);
    setAttribute(Qt::WA_X11DoNotAcceptFocus, true);
    setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);

    QFont ft;
    ft.setPointSize(12);
    ui -> textBrowser -> setFont(ft);

    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::red); 
    ui -> textBrowser -> setPalette(pa);

    my_course = new tea_course(_id, this);
    ui -> tabWidget -> addTab(my_course, tr("我的课程"));
}

//删除课程
void teachermanage::delCourse(int course_id, QString name)
{
    emit MsendData(tr("4 ") + QString::number(course_id));
    int index = findTab(name);     //将该课程从子窗口中删除
    if(index)
        ui -> tabWidget -> removeTab(index);
}

//更新窗口
void teachermanage::updatewidget(QStringList &list, bool flag, QString name)
{
    if(!flag)
        my_course -> update(list);
    else
    {
         int index = findTab(name);
         if(index)
         {
             dynamic_cast<course_student*>(ui -> tabWidget->widget(index)) -> update(list);
         }
    }
}

//查找该课程的子窗口
int teachermanage::findTab(QString name)
{
    for(int i = 1; i < ui -> tabWidget -> count(); i++)
    {
        if(name == ui -> tabWidget -> tabText(i))//名字相同
            return i;
    }
    return 0;
}

//添加课程子窗口
void teachermanage::add_course_Tab(int course_id, QString name)
{
    int index = findTab(name);
    if(index)                                       //Tabwidget中已有该课程窗口，则跳转到该窗口
        ui -> tabWidget -> setCurrentIndex(index);
    else                                            //否则新建子窗口
    {
        childwidget *new_tab = new course_student(course_id, this);
        connect(new_tab, SIGNAL(sendData(QString)), this, SLOT(manageSend(QString)));
        ui -> tabWidget -> addTab(new_tab, name);
        ui -> tabWidget -> setCurrentWidget(new_tab);
    }
    manageSend(tr("7 ") + QString::number(course_id));
}

//显示学生具体信息
void teachermanage::showdetail(QStringList &list)
{
    qDebug() << "showDetail";
    ui -> textBrowser -> setText(tr("学生信息如下:\n\n\n") +
                                 tr("编号: \n   ") + list[1] +
                                 tr("\n姓名: \n   ") + list[2] +
                                 tr("\n年级: \n   ") + list[3]);
}

teachermanage::~teachermanage()
{
    delete my_course;
    for(int i = 1; i < ui -> tabWidget -> count(); i++)
    {
        delete ui -> tabWidget -> widget(i);
    }
    delete ui;
}


