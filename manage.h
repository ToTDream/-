#ifndef MANAGE_H
#define MANAGE_H

#include <map>
#include <vector>
#include <QWidget>
#include "person.h"
#include "course.h"
#include "childwidget.h"
class childwidget;
class course;
class person;
class manage : public QWidget
{
    Q_OBJECT
public:
    explicit manage(QWidget*);

    person *one;
    childwidget *showAllWidget;
    std::vector<person*> all_person;
    std::vector<course*> all_course;
    person* findPerson(int);
    course* findCourse(int);
    virtual void updatewidget(){}

    ~manage();
    void read();
    void write();
protected:
    void read(QString, bool);
    void write(QString, bool);
signals:
public slots:
    virtual void showdetail(int){}
    virtual void addCourse(int){}
    virtual void delCourse(int){}
    void showAllCourse();
};

#endif // MANAGE_H
