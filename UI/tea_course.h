#ifndef TEA_COURSE_H
#define TEA_COURSE_H
#include "childwidget.h"
class tea_course : public childwidget
{
    Q_OBJECT
public:
    tea_course(int, manage*);
    ~tea_course();
    void update(QStringList& list);
private:
    QPushButton *post, *reset;
signals:
    void call_add_tab(int, QString);                 //添加该课程的子窗口（显示该课程学生
    void call_del_tab(int, QString);                 //删除该课程子窗口
private slots:
    void post_clicked();                    //提交删除课程
    void reset_clicked();                   //重置信息
    void show_course_student(int, int);     //双击课程响应，显示该课程的所有学生
};

#endif // TEA_COURSE_H
