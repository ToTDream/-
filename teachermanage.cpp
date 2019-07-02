#include <qDebug>
#include <QDialog>
#include <QMessageBox>
#include "tea_course.h"
#include <inquiredialog.h>
#include "teachermanage.h"
#include "course_student.h"
#include "ui_teachermanage.h"

teachermanage::teachermanage(int _id, QString _name, QString _academy, QWidget *parent):
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
    if(!one)
        one = new teacher(_id, _name, _academy);
    my_course = new tea_course(one -> get_id(), this);
    ui -> tabWidget -> addTab(my_course, tr("我的课程"));
    my_course -> update();
    qDebug() << "teachermanage";
}

//添加课程
void teachermanage::addCourse(int course_id, QString name, int credit, bool flag)
{
    one -> add(course_id, credit);
    course *ans;
    if(flag)
         ans = new require_course(course_id, credit, name);
    else ans = new optional_course(course_id, credit, name);

    all_course.push_back(ans);
    updatewidget();
}
//删除课程
void teachermanage::delCourse(int course_id)
{
    course *ans = findCourse(course_id);

    std::map<int, int>::iterator iter;
    for(iter = ans -> student_map.begin(); iter != ans -> student_map.end(); iter++)
    {
        if(~iter -> second)
        {
            inquiredialog *dialog = new inquiredialog(tr("该课程学生成绩已经公布，确认删除?"), this);
            dialog -> setWindowTitle(tr("删除课程确认"));

            if(dialog -> exec() == QDialog::Rejected){qDebug() << "no";return;}
            else break;
        }
    }
    qDebug() << "yes";
    one -> del(course_id);
    foreach(person *p, all_person)
    {
        p -> course_map.erase(course_id);
    }
    int index = findTab(course_id);
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
        if(findCourse(course_id) -> get_name() == ui -> tabWidget -> tabText(i))
            return i;
    }
    return 0;
}
//添加课程子窗口
void teachermanage::add_course_Tab(int course_id)
{
    qDebug() << "add_course_Tab";
    int index = findTab(course_id);
    if(index)
        ui -> tabWidget -> setCurrentIndex(index);
    else
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
    stu -> course_map[course_id] = score;
    course *co = findCourse(course_id);
    co -> student_map[student_id] = score;
    qDebug() << "修改" << co -> student_map[student_id] << " "<< stu -> course_map[course_id];
}

teachermanage::~teachermanage()
{
    delete ui;
}


