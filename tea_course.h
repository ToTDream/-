#ifndef TEA_COURSE_H
#define TEA_COURSE_H
#include "childwidget.h"
class tea_course : public childwidget
{
    Q_OBJECT
public:
    tea_course(int, manage*);
    void update();
private:
    QPushButton *post, *reset;
    QPushButton *addButton;
signals:
    void call_add_tab(int);
    void call_del_tab(int);
private slots:
    void add();
    void post_clicked();
    void reset_clicked();
    void show_course_student(int, int);
};

#endif // TEA_COURSE_H
