#ifndef COURSE_STUDENT_H
#define COURSE_STUDENT_H

#include "childwidget.h"
class course_student : public childwidget
{
    Q_OBJECT
public:
    int tmp;                                //暂存变量，确认更改分数前保存更改前的值
    course_student(int, manage*);
    void update(QStringList &list);                          //更新窗口
signals:
    void post_change_id(int, int, int);     //提交改变分数的学生id，课程id及更改后的分数
private:
    int id;
private slots:
    void getItem(int, int);                 //获取点击位置
    void post_clicked();                    //提交更改分数
    void get_changeItem(int, int);          //获取更改位置
};

#endif // COURSE_STUDENT_H
