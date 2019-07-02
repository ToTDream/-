#include "person.h"
person::person(int _id, QString _name)
{
    id = _id, name = _name;
}

student::student(int _id, QString _name, int _class):
    person(_id, _name), Class(_class)
{
    flag = false;
    course_map.clear();
}
void student::add(int course_id)
{
    course_map.insert(std::make_pair(course_id, -1));
}
void student::del(int course_id)
{
    course_map.erase(course_id);
}
void student::show()
{

}
void student::set(QString _id, QString _name, QString _class)
{
    id = _id.toInt();
    name = _name;
    Class = _class.toInt();
}
teacher::teacher(int _id, QString _name, QString _academy):
    person(_id, _name), academy(_academy)
{
    flag = true;
    course_map.clear();
}

void teacher::add(int course_id, int credit)
{
    course_map.insert(std::make_pair(course_id, credit));
}

void teacher::del(int course_id)
{
    course_map.erase(course_id);
}

void teacher::show()
{

}
void teacher::set(QString _id, QString _name, QString _academy)
{
    id = _id.toInt();
    name = _name;
    academy = _academy.toInt();
}
