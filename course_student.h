#ifndef COURSE_STUDENT_H
#define COURSE_STUDENT_H

#include "childwidget.h"
class course_student : public childwidget
{
    Q_OBJECT
public:
    int tmp;                                //暂存变量，确认更改分数前保存更改前的值
    course_student(int, manage*);
signals:
    void post_show_id(int);                 //提交点击学生的id
    void post_change_id(int, int, int);     //提交改变分数的学生id，课程id及更改后的分数
private:
    course *cur_course;                     //该课程的类指针
    void update();                          //更新窗口
private slots:
    void getItem(int, int);                 //获取点击位置
    void post_clicked();                    //提交更改分数
    void get_changeItem(int, int);          //获取更改位置
};

#endif // COURSE_STUDENT_H
