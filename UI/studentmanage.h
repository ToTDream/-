#ifndef STUDENTMANAGE_H
#define STUDENTMANAGE_H

#include <QWidget>
#include "manage.h"
#include "childwidget.h"

namespace Ui {
class studentmanage;
}
class studentmanage : public manage
{
    Q_OBJECT
public:
    studentmanage(int, QWidget *parent = 0);
    ~studentmanage();
    void addCourse(int);            //添加课程
    void delCourse(int);            //删除课程
private:
    Ui::studentmanage *ui;
    childwidget *selected_course;   //Tab子窗口，显示已选课程
    childwidget *optional_course;   //Tab子窗口，显示可选课程
signals:

private slots:
    void updatewidget(QStringList&, bool);            //更新窗口数据
};
#endif // STUDENTMANAGE_H
