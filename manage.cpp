#include <QFont>
#include <QFile>
#include <QDebug>
#include <QString>
#include <QPalette>
#include "manage.h"
#include <QTextStream>
#include <qtextcodec.h>
#include <QMessageBox>
manage::manage(QWidget *parent = nullptr)
{
    all_course.clear();
    all_person.clear();
    showAllWidget = nullptr;
    read();
}
person* manage::findPerson(int person_id)
{
    foreach(person *one, all_person)
        if(one -> get_id() == person_id)return one;
    return nullptr;
}
course* manage::findCourse(int course_id)
{
    foreach(course *one, all_course)
        if(one -> get_id() == course_id)return one;
    return nullptr;
}
void manage::read()
{
    read("D:/QT/C++/student_system(1)/files/teacher.txt", true);
    read("D:/QT/C++/student_system(1)/files/student.txt", false);
}
void manage::write()
{
    write("D:/QT/C++/student_system(1)/files/teacher.txt", true);
    write("D:/QT/C++/student_system(1)/files/student.txt", false);
}
void manage::read(QString filename, bool kind)
{
    qDebug() << "read";
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);

    QFile file(filename);
    try
    {
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
            throw QString(tr("can't open the") + filename);

        while(!file.atEnd())
        {
            QByteArray line = file.readLine();
            QString _str(line);
            QStringList list = _str.remove("\n").split(" ");

            if(kind)
                one = new teacher(list[0].toInt(), list[1], list[2]);
            else
                one = new student(list[0].toInt(), list[1], list[2].toInt());

            all_person.push_back(one);
            if(kind)
                for(int i = 3; i < list.size(); i += 4)
                {
                    if(list[i+3] == "yes")
                        all_course.push_back(new require_course(list[i].toInt(), list[i+2].toInt(), list[i+1]));
                    else
                        all_course.push_back(new optional_course(list[i].toInt(), list[i+2].toInt(), list[i+1]));
                    one -> course_map.insert(std::make_pair(list[i].toInt(), list[i+2].toInt()));
                }
            else
                for(int i = 3; i < list.size(); i += 2)
                {
                    one -> course_map.insert(std::make_pair(list[i].toInt(), list[i+1].toInt()));
                    course *co = findCourse(list[i].toInt());
                    if(co)co -> student_map.insert(std::make_pair(list[0].toInt(), list[i+1].toInt()));
                }
        }
        file.close();
    }
    catch(QString e)
    {
        QMessageBox::about(this, "Error!", e);
    }
}

void manage::write(QString filename, bool flag)
{
    qDebug() << "write";
    QFile file(filename);
    try
    {
        if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
            throw QString(tr("can't open the") + filename);
        QTextStream in(&file);
        foreach(person *one, all_person)
        {
            if(flag && one -> flag)
                in << one -> get_id() << " " << one -> get_name() << " " << one -> get_academy();
            else if(!flag && !one -> flag)
                in << one -> get_id() << " " << one -> get_name() << " " << one -> get_class();
            else continue;

            std::map<int, int>::iterator iter;
            for(iter = one -> course_map.begin(); iter != one -> course_map.end(); iter++)
            {
                if(one -> flag)
                {
                    course *co = findCourse(iter -> first);
                    in << " " << iter -> first << " " << co -> get_name() << " " << iter -> second << " " << (co -> flag ? "yes" : "no");
                }
                else
                    in << " " << iter -> first << " " << iter -> second;
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

manage::~manage(){
    delete showAllWidget;
    showAllWidget = nullptr;
}
