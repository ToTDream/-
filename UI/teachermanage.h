#ifndef TEACHERMANAGE_H
#define TEACHERMANAGE_H

#include <QWidget>
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
    void showdetail(QStringList&);                       //显示学生详细详细
private:
    Ui::teachermanage *ui;
    childwidget *my_course;
    int findTab(QString);                       //查找课程的子窗口编号
signals:
private slots:
    void updatewidget(QStringList&, bool, QString);      //更新子窗口
    void delCourse(int, QString);                        //删除课程
    void add_course_Tab(int, QString);                   //添加子窗口
//    void change_score(int, int, int);           //更改/提交成绩
};

#endif // TEACHERMANAGE_H
