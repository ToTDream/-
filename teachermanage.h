#ifndef TEACHERMANAGE_H
#define TEACHERMANAGE_H

#include <QWidget>
#include "person.h"
#include "course.h"
#include "manage.h"
#include "tea_course.h"

namespace Ui {
class teachermanage;
}

class teachermanage : public manage
{
    Q_OBJECT
public:
    teachermanage(int, QWidget *parent = 0);
    ~teachermanage();
    void delCourse(int);                        //删除课程
private:
    Ui::teachermanage *ui;
    childwidget *my_course;
    int findTab(int);                           //查找课程的子窗口编号
signals:
private slots:
    void updatewidget();                        //更新子窗口
    void showdetail(int);                       //显示学生详细详细
    void add_course_Tab(int);                   //添加子窗口
    void change_score(int, int, int);           //更改/提交成绩
    void addCourse(int, QString, int, bool);    //添加课程
};

#endif // TEACHERMANAGE_H
