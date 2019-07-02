#include <QDebug>
#include "person.h"
#include <QHBoxLayout>
#include "stu_selected.h"
#include "stu_optional.h"
#include "studentmanage.h"
#include "ui_studentmanage.h"
studentmanage::studentmanage(int _id, QString _name, int Class, QWidget *parent) :
    manage(parent),
    ui(new Ui::studentmanage)
{
    ui->setupUi(this);
    setParent(parent);
    setAttribute(Qt::WA_X11DoNotAcceptFocus, true);
    setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);

    QFont ft;
    ft.setPointSize(12);
    ui -> info_title -> setFont(ft);
    ft.setPointSize(10);
    ui -> detail -> setFont(ft);

    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::red);
    ui -> info_title->setPalette(pa);
    pa.setColor(QPalette::WindowText,Qt::black);
    ui -> detail -> setPalette(pa);

    ui -> info_title->setText(tr("  信息展示栏"));
    one = findPerson(_id);
    if(!one)
    {
        one = new student(_id, _name, Class);
        foreach(course *it, all_course)
            if(it -> flag)
               one -> course_map.insert(std::make_pair(it -> get_id(), -1));
    }
    selected_course = new stu_selected(one -> get_id(), this);
    connect(selected_course, SIGNAL(post_show_id(int)), this, SLOT(show_GPA(int)));
    optional_course = new stu_optional(one-> get_id(), this);
    ui -> tabWidget -> addTab(selected_course, tr("已选课程"));
    ui -> tabWidget -> addTab(optional_course, tr("可选课程"));
    updatewidget();
}
//更新窗口
void studentmanage::updatewidget()
{
    selected_course -> update();
    optional_course -> update();
}

studentmanage::~studentmanage()
{
    delete ui;
}
//添加课程
void studentmanage::addCourse(int course_id)
{
    one -> add(course_id);
    course *ans = findCourse(course_id);
    ans -> student_map.insert(std::make_pair(one -> get_id(), -1));
}
//删除课程
void studentmanage::delCourse(int course_id)
{
    one -> del(course_id);
    course *ans = findCourse(course_id);
    ans -> student_map.erase(one -> get_id());
    updatewidget();
}
//显示GPA
void studentmanage::show_GPA(int course_id)
{
    if(one -> course_map[course_id] == -1)
    {
        ui -> detail -> setText(tr("分数未知，无法查看绩点"));
        return;
    }
    course * co = findCourse(course_id);
    ui -> detail -> setText(tr("该课程绩点为:\n") + QString::number(co -> get_GPA(this, one -> get_id())));
}
