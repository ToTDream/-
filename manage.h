#ifndef MANAGE_H
#define MANAGE_H

#include <map>
#include <vector>
#include <QWidget>
#include "person.h"
#include "course.h"
#include <QStringlist>
#include "childwidget.h"
#include "sort_template.h"
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
    std::vector<person*> all_person;            //所有学生/老师
    std::vector<course*> all_course;            //所有课程
    person* findPerson(int);                    //获取对应id的学生/老师的类指针
    course* findCourse(int);                    //获取对应id的课程类指针
    virtual void updatewidget(){}               //更新窗口

    ~manage();
    void read();                                //读取数据
    void write();                               //写入数据
protected:
    void read(QString, bool);                   //读取指定文件的数据
    void write(QString, bool);                  //将数据写入指定文件
signals:
public slots:
    void showAllCourse();                       //显示所有课程
    virtual void delCourse(int){}               //删除课程
    virtual void addCourse(int){}               //添加课程
    virtual void showdetail(int){}              //显示详细信息
};

QStringList & operator >>(QStringList&, std::vector<course*> &);//重载>>,将数据由QStringlist中读入到course vector中

#endif // MANAGE_H
