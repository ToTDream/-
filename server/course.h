#ifndef COURSE_H
#define COURSE_H

#include <map>
#include <vector>
#include <QColor>
#include <QString>
#include "server.h"
#include <algorithm>

class server;

class course
{
public:
    course(int, int, QString);
    std::map<int, int> student_map;                 //学生学号及分数
    bool flag;                                      //区别老师学生
    void set();                                     //写值
    void add(int);                                  //添加学生
    inline int get_id(){return id;}                 //读取id
    inline int get_credit(){return credit;}         //读取学分
    inline QString get_name(){return name;}         //读取姓名
    virtual float get_GPA(server*, int){return -1;} //计算GPA
protected:
    int id;                                         //id
    int credit;                                     //学分
    QString name;                                   //姓名
};

QTextStream& operator <<(QTextStream&, course&);    //重载<<，将文件内容读入course

class require_course:public course
{
public:
    require_course(int, int, QString);

    float get_GPA(server *, int);

	~require_course();
};

class optional_course:public course
{
public:
    optional_course(int, int, QString);

    float get_GPA(server*, int);

	~optional_course();
};

#endif // COURSE_H
