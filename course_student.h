#ifndef COURSE_STUDENT_H
#define COURSE_STUDENT_H

#include "childwidget.h"
class course_student : public childwidget
{
    Q_OBJECT
public:
    int tmp;
    course_student(int, manage*);
signals:
    void post_show_id(int);
    void post_change_id(int, int, int);
private:
    course *cur_course;
    void update();
private slots:
    void getItem(int, int);
    void get_changeItem(int, int);
    void post_clicked();
};

#endif // COURSE_STUDENT_H
