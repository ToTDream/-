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
    teachermanage(int, QString, QString, QWidget *parent = 0);
    ~teachermanage();
    void delCourse(int);
private:
    Ui::teachermanage *ui;
    childwidget *my_course;
    int findTab(int);
signals:
private slots:
    void showdetail(int);
    void change_score(int, int, int);
    void addCourse(int, QString, int, bool);
    void add_course_Tab(int);
    void updatewidget();
};

#endif // TEACHERMANAGE_H
