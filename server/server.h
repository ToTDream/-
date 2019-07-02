#ifndef SERVER_H
#define SERVER_H

#include <map>
#include <QDebug>
#include <vector>
#include <QWidget>
#include "person.h"
#include "course.h"
#include <QStringlist>
#include "sort_template.h"
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpsocket>

typedef std::pair<int,int> pair;
typedef std::vector<pair> pair_vec;

enum SToCCmd{
                CheckPwAns = 1, CourseOfTeacher, StudentOfCourse,
                SelectCourse, OptionalCourse, AllCourse, DetailOfStudent

            };

enum CToSCmd{
                ChangePw = 1, CheckPw, AddCourse,
                DelCourse, GetCourse, GetDetail,
                GetStudent,GetAllCourse, ChangeScore,
                GetSelect, GetOptional, disConnect,sortFirst, sortSecond
            };
class course;
class person;
class server : public QWidget
{
    Q_OBJECT

public:
    server(QWidget *parent = 0);
    ~server();
    void write();                               //写入数据
    void writePassword();
private:
    int blockSize;
    QTcpServer *tcpserver;
    QTcpSocket *tcpsocket;
    std::vector<person*> all_person;            //所有学生/老师
    std::vector<course*> all_course;            //所有课程
    std::map<int, QString> password;
    std::map<int, QTcpSocket*>all_socket;
    person* findPerson(int);                    //获取对应id的学生/老师的类指针
    course* findCourse(int);                    //获取对应id的课程类指针
    int findTeacherOfCourse(int);
    void read();                                //读取数据
    void write(QString, bool);                  //将数据写入指定文件
    void read(QString, bool);                   //读取指定文件的数据
    void addCourse(int, QStringList&);
    void delCourse(int, int);
    void getDetail(int, int);
    void getCourse(int);
    void getAllCourse(int);
    void getSelectCourse(int);
    void getOptionalCourse(int);
    void getStudent(int, int);
    std::vector<pair> SortFirst(int, int);
    std::vector<pair> SortSecond(int, int);
    void changeSortKind(int);
    void readPassword();
    void checkPassword(int, QString);
    void changePassword(int, QString);
    void changeScore(int, int, QStringList&);
    void sendData(int, QString);
signals:
public slots:
    void deletesocket(int);
    void createConnection();
    void readData();
};

#endif // SERVER_H
