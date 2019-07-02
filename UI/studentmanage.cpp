#include <QDebug>
#include <QHBoxLayout>
#include "stu_selected.h"
#include "stu_optional.h"
#include "studentmanage.h"
#include "ui_studentmanage.h"
studentmanage::studentmanage(int _id, QWidget *parent) :
    manage(parent),
    ui(new Ui::studentmanage)
{
    ui->setupUi(this);
    setParent(parent);
    setAttribute(Qt::WA_X11DoNotAcceptFocus, true);
    setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);

    QFont ft;
    ft.setPointSize(12);
    ft.setPointSize(10);

    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::red);
    pa.setColor(QPalette::WindowText,Qt::black);

    selected_course = new stu_selected(id, this);
    connect(selected_course, SIGNAL(sendData(QString)), this, SLOT(manageSend(QString)));

    optional_course = new stu_optional(id, this);
    connect(optional_course, SIGNAL(sendData(QString)), this, SLOT(manageSend(QString)));

    ui -> tabWidget -> addTab(selected_course, tr("已选课程"));
    ui -> tabWidget -> addTab(optional_course, tr("可选课程"));
}
//更新窗口
void studentmanage::updatewidget(QStringList &list, bool flag)
{
    if(flag)
         selected_course -> update(list);
    else optional_course -> update(list);
}

//添加课程
void studentmanage::addCourse(int course_id)
{
    manageSend(tr("3 ") + QString::number(course_id));
}
//删除课程
void studentmanage::delCourse(int course_id)
{
    manageSend(tr("4  ") + QString::number(course_id));
}

studentmanage::~studentmanage()
{
    delete selected_course;
    delete optional_course;
    delete ui;
}
