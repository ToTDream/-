#ifndef PERSON_H
#define PERSON_H
#include <map>
#include <QString>
#include <algorithm>
#include <QStringList>
#include <QTextStream>
class person
{
public:
    person();
    person(int, QString);
    std::map<int, int> course_map;                  //对应的课程id及分数/学分
    bool flag;                                      //区别老师，学生
    virtual void add(int){}                         //添加课程
    virtual void del(int){}                         //删除课程
    virtual void add(int, int){}                    //删除课程
    virtual void set(QString, QString, QString){}   //各变量置值
    inline  int  get_id(){return id;}               //获取id
    virtual int  get_class(){return -1;}            //获取班级
    inline  QString get_name(){return name;}        //获取姓名
    virtual QString get_academy(){return "未知";}   //获取学院
protected:
    int id;
	QString name;
};
QTextStream& operator <<(QTextStream &, person &);//重载<<，将数据由文件流读入person类

class student:public person
{
public:
    student();
	student(int, QString, int);
    void add(int);
    void del(int);
    void set(QString, QString, QString);
    inline int get_class(){return Class;}
    ~student();
protected:
    int Class;
};

QStringList& operator >>(QStringList&, student&);//将数据由QStringlist读入student
QTextStream& operator <<(QTextStream&, student&);//将数据由student读入文件

class teacher:public person
{
public:
    teacher();
	teacher(int, QString, QString);
    void del(int);
    void add(int, int);
    void set(QString, QString, QString);
    inline QString get_academy(){return academy;}
    ~teacher();
protected:
    QString academy;
};

QStringList& operator >>(QStringList&, teacher&);//将数据由Qstringlist读入teacher
QTextStream& operator <<(QTextStream&, teacher&);//将数据由teacher读入文件

#endif // PERSON_H
