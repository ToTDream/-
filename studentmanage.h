#ifndef STUDENTMANAGE_H
#define STUDENTMANAGE_H

#include <QWidget>
#include "person.h"
#include "course.h"
#include "manage.h"
#include "childwidget.h"

namespace Ui {
class studentmanage;
}

class studentmanage : public manage
{
    Q_OBJECT
public:
    studentmanage(int, QString, int, QWidget *parent = 0);
    ~studentmanage();
    void addCourse(int);
    void delCourse(int);
private:
    Ui::studentmanage *ui;
    childwidget *selected_course;
    childwidget *optional_course;
signals:

private slots:
    void updatewidget();
    void show_GPA(int);
};

#endif // STUDENTMANAGE_H
