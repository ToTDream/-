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

    one = findPerson(_id);
    my_course = new tea_course(one -> get_id(), this);
    ui -> tabWidget -> addTab(my_course, tr("我的课程"));
    my_course -> update();
}

//添加课程
void teachermanage::addCourse(int course_id, QString name, int credit, bool flag)
{
    one -> add(course_id, credit);

    course *ans;
    if(flag)                                //必修课
    {
        ans = new require_course(course_id, credit, name);
        foreach(person *p, all_person)
        {
            if(!p -> flag)
            {
                ans -> student_map.insert(std::make_pair(p -> get_id(), -1));
                p -> course_map.insert(std::make_pair(course_id, -1));
            }
        }
        qDebug() << ans -> student_map.size();
    }
    else                                    //选修课
         ans = new optional_course(course_id, credit, name);
    all_course.push_back(ans);

    updatewidget();                         //更新窗口
}

//删除课程
void teachermanage::delCourse(int course_id)
{
    course *ans = findCourse(course_id);

    std::map<int, int>::iterator iter;
    for(iter = ans -> student_map.begin(); iter != ans -> student_map.end(); iter++)
    {
        //有至少一位学生成绩已知则判断是否删除
        if(~iter -> second)
        {
            if(QMessageBox::question(this, "确认删除", "该课程学生成绩已经公布，确认删除?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
                break;
            else
                return;
        }
    }
//    one -> del(course_id);
    foreach(person *p, all_person)
    {
        p -> course_map.erase(course_id);
    }
    int index = findTab(course_id);     //将该课程从子窗口中删除
    if(index)
        ui -> tabWidget -> removeTab(index);
}

//更新窗口
void teachermanage::updatewidget()
{
    my_course -> update();

}

//查找该课程的子窗口
int teachermanage::findTab(int course_id)
{
    for(int i = 1; i < ui -> tabWidget -> count(); i++)
    {
        if(findCourse(course_id) -> get_name() == ui -> tabWidget -> tabText(i))//名字相同
            return i;
    }
    return 0;
}

//添加课程子窗口
void teachermanage::add_course_Tab(int course_id)
{
    int index = findTab(course_id);
    if(index)                                       //Tabwidget中已有该课程窗口，则跳转到该窗口
        ui -> tabWidget -> setCurrentIndex(index);
    else                                            //否则新建子窗口
    {
        childwidget *new_tab = new course_student(course_id, this);
        connect(new_tab, SIGNAL(post_change_id(int, int, int)), this, SLOT(change_score(int, int, int)));
        ui -> tabWidget -> addTab(new_tab, findCourse(course_id)->get_name());
        ui -> tabWidget -> setCurrentWidget(new_tab);
    }
    update();
}

//显示学生具体信息
void teachermanage::showdetail(int student_id)
{
    person *one = findPerson(student_id);
    ui -> textBrowser -> setText(tr("学生信息如下:\n\n\n") +
                                 tr("编号: \n   ") + QString::number(one -> get_id()) +
                                 tr("\n姓名: \n   ") + one -> get_name() +
                                 tr("\n年级: \n   ") + QString::number(one -> get_class()));
}

//修改分数
void teachermanage::change_score(int student_id, int course_id, int score)
{
    person *stu = findPerson(student_id);
    stu -> course_map[course_id] = score;//修改学生课程容器
    course *co = findCourse(course_id);
    co -> student_map[student_id] = score;//修改课程学生容器
    qDebug() << "修改" << co -> student_map[student_id] << " "<< stu -> course_map[course_id];
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


