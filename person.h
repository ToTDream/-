#ifndef PERSON_H
#define PERSON_H
#include <map>
#include <QString>
class person
{
public:
    person(int, QString);
    std::map<int, int> course_map;
    bool flag;
    virtual void add(int){}
    virtual void add(int, int){}
    virtual void del(int){}
    virtual void set(QString, QString, QString){}
    inline int get_id(){return id;}
    inline QString get_name(){return name;}
    virtual int get_class(){}
    virtual QString get_academy(){}
protected:
    int id;
	QString name;
};
class student:public person
{
public:
    student();
	student(int, QString, int);
    void add(int);
    void del(int);
    void show();
    void set(QString, QString, QString);
    inline int get_class(){return Class;}
	~student();
protected:
    int Class;
};

class teacher:public person
{
public:
    teacher();
	teacher(int, QString, QString);
    void add(int, int);
    void del(int);
	void show();
    void set(QString, QString, QString);
    inline QString get_academy(){return academy;}
	~teacher();
protected:
    QString academy;
};
#endif // PERSON_H
