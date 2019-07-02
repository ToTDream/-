#ifndef COURSE_H
#define COURSE_H

#include <map>
#include <vector>
#include <QColor>
#include <QString>
#include "manage.h"

class manage;

class course
{
public:
    course(int, int, QString);
    std::map<int, int> student_map;
    bool flag;
    virtual float get_GPA(manage*, int){}
    void show(){}
    void set();
    int add(int);
    inline int get_id(){return id;}
    inline int get_credit(){return credit;}
    inline QString get_name(){return name;}
protected:
	int id;
	int credit;
    QString name;
    QColor backcolor;
};
class require_course:public course
{
public:
    require_course(int, int, QString);

    float get_GPA(manage *, int);

	~require_course();
};
class optional_course:public course
{
public:
    optional_course(int, int, QString);

    float get_GPA(manage*, int);

	~optional_course();
};

#endif // COURSE_H
