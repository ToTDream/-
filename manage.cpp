#include <QFont>
#include <QFile>
#include <QDebug>
#include <QString>
#include <QPalette>
#include "manage.h"
#include <QTextStream>
#include <qtextcodec.h>
#include <QMessageBox>
#include <fstream>
manage::manage(QWidget *parent = nullptr)
{
    setWindowIcon(QIcon(":/image/main.jpg"));
    setWindowTitle(tr("教务管理系统"));
    all_course.clear();
    all_person.clear();
    showAllWidget = nullptr;
    read();
}
//查找对应id的person指针
person* manage::findPerson(int person_id)
{
    foreach(person *one, all_person)
        if(one -> get_id() == person_id)return one;
    return nullptr;
}
//查找对应id的课程指针
course* manage::findCourse(int course_id)
{
    foreach(course *one, all_course)
        if(one -> get_id() == course_id)return one;
    return nullptr;
}
//读取数据
void manage::read()
{
    read("D:/QT/MD/files/teacher.txt", true);
    read("D:/QT/MD/files/student.txt", false);
}
//保存/更新数据
void manage::write()
{
    write("D:/QT/MD/files/teacher.txt", true);
    write("D:/QT/MD/files/student.txt", false);
}
//重载>>,将数据由QStringlist读入到all_course中
QStringList& operator >>(QStringList &list, std::vector<course*> &vt)
{
    for(int i = 3; i < list.size(); i += 4)
    {
        course *c;
        QString name = list[i+1];
        if(list[i+3] == "yes")//必修课
            c = new require_course(list[i].toInt(), list[i+2].toInt(), name);
        else                  //选修课
            c = new optional_course(list[i].toInt(), list[i+2].toInt(), name);
        vt.push_back(c);
    }
    return list;
}
void manage::read(QString filename, bool kind)
{
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);

    QFile file(filename);
    try
    {
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
            throw QString(tr("can't open the") + filename);     //打开文件失败，抛出异常
        while(!file.atEnd())
        {        
            QByteArray line = file.readLine();                  //读取一行
            QString _str(line);
            QStringList list = _str.remove("\n").split(" ");    //去除末尾换行，按空格分隔
            person *p;
            if(kind)                                            //teacher.txt的数据输入到老师及课程类中
            {                
                teacher* t = new teacher;
                list >> *t;
                list >> all_course;
                p = t;
            }
            else                                                //student.txt的数据读入到学生及课程类中
            {               
                student *s = new student;
                list >> *s;
                p = s;
                for(int i = 3; i < list.size(); i += 2)
                {
                    course *co = findCourse(list[i].toInt());
                    if(co)co -> student_map.insert(std::make_pair(list[0].toInt(), list[i+1].toInt()));
                }
            }
            all_person.push_back(p);                            //学生，老师类指针存入all_person
        }
        file.close();
    }
    catch(QString e)                                            //捕获异常
    {
        QMessageBox::about(this, "Error!", e);
    }
}

void manage::write(QString filename, bool flag)
{
    QFile file(filename);
    try
    {
        if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
            throw QString(tr("can't open the") + filename);
        QTextStream in(&file);
        foreach(person *one, all_person)
        {
            if(flag && one -> flag)in << *one;                  //教师类
            else if (!flag && !one -> flag)in << *one;          //学生类
            else continue;

            if(flag)//teacher.txt 写入课程详细信息
            {
                std::map<int, int>::iterator iter;
                for(iter = one -> course_map.begin(); iter != one -> course_map.end(); iter++)
                {
                    course *co = findCourse(iter -> first);
                    in << *co;                                  //课程数据写入文件
                }
            }
            in << "\n";
        }
        file.close();
    }
    catch(QString e)
    {
        QMessageBox::about(this, "Error!", e);
    }
}
void manage::showAllCourse()
{
    if(!showAllWidget) showAllWidget = new childwidget(this);
    showAllWidget -> update();
    showAllWidget -> show();
}

manage::~manage()
{
    delete showAllWidget;
    showAllWidget = nullptr;
}
