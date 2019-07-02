#include "person.h"
#include <QDebug>
#include <QString>
person::person()
{
    course_map.clear();
}
person::person(int _id, QString _name)
{
    id = _id, name = _name;
}
QTextStream& operator <<(QTextStream &out, person &p)
{
    out << p.get_id() << " " << p.get_name() << " ";

    if(p.flag)
        out << p.get_academy();
    else
    {
        out << p.get_class();
        std::map<int, int>::iterator iter;
        for(iter = p.course_map.begin(); iter != p.course_map.end(); iter++)
        {
            out << " " << iter -> first << " " << iter -> second;
        }
    }
    return out;
}

student::student()
{
    flag = false;
    course_map.clear();
}

student::student(int _id, QString _name, int _class):
    person(_id, _name), Class(_class)
{
    flag = false;
    course_map.clear();
}
//添加课程
void student::add(int course_id)
{
    course_map.insert(std::make_pair(course_id, -1));
}
//删除课程
void student::del(int course_id)
{
    course_map.erase(course_id);
}
//置值
void student::set(QString _id, QString _name, QString _class)
{
    id = _id.toInt();
    name = _name;
    Class = _class.toInt();
    if(!id || !Class)throw QString("学生数据格式异常。");     //抛出异常
}
//重载>>,将数据由QStringlist写入student中
QStringList& operator >>(QStringList &list, student &s)
{
    try
    {
        s.set(list[0], list[1], list[2]);           //前三个数为id, name, Class
        for(int i = 3; i < list.size(); i += 2)     //已选课程录入
        {
            if(!list[i].toInt())throw QString("学生课程格式异常。");//抛出异常
            s.course_map.insert(std::make_pair(list[i].toInt(), list[i+1].toInt()));
        }
        return list;
    }
    catch(QString e)                                //捕获异常，抛给上层
    {
        throw e;
    }
}
//重载<<，将数据由student写入文件中
QTextStream& operator <<(QTextStream &out, student &s)
{
    out << s.get_id() << " " << s.get_name() << " " << s.get_class();
    std::map<int, int>::iterator iter;
    for(iter = s.course_map.begin(); iter != s.course_map.end(); iter++)
    {
        out << " " << iter -> first << " " << iter -> second;
    }
    out << "\n";
    return out;
}
student::~student()
{

}

teacher::teacher()
{
    flag = true;
    course_map.clear();
}
teacher::teacher(int _id, QString _name, QString _academy):
    person(_id, _name), academy(_academy)
{
    flag = true;
    course_map.clear();
}
//添加课程
void teacher::add(int course_id, int credit)
{
    course_map.insert(std::make_pair(course_id, credit));
}
//重载>>,将数据由QStringList读入teacher中
QStringList& operator >>(QStringList &list, teacher &t)
{
    try
    {
        t.set(list[0], list[1], list[2]);
        for(int i = 3; i < list.size(); i += 4)
        {
            if(!list[i].toInt() || !list[i+2].toInt())throw QString("老师课程格式异常。");
            t.course_map.insert(std::make_pair(list[i].toInt(), list[i+2].toInt()));
        }
        return list;
    }
    catch(QString e)
    {
        throw e;
    }
}
//重载<<，将数据由teacher写入文件中
QTextStream& operator <<(QTextStream &out, teacher &t)
{
    out << t.get_id() << " " << t.get_name() << " " << t.get_academy();
    return out;
}
//删除课程
void teacher::del(int course_id)
{
    course_map.erase(course_id);
}
//置值
void teacher::set(QString _id, QString _name, QString _academy)
{
    id = _id.toInt();
    name = _name;
    academy = _academy;
    if(!id)throw QString("老师数据格式异常。");
}

teacher::~teacher()
{

}
