#include "server.h"
#include <QFile>
#include <QTextCodec>
#include <QMessageBox>
server::server(QWidget *parent)
    : QWidget(parent)
{
    tcpserver = new QTcpServer(this); //服务器监听类
    if(!tcpserver->listen(QHostAddress::LocalHost,6666)) //服务器监听本机所有IP的12345端口
    {

       qDebug() << tcpserver->errorString(); //Debug出错误信息
       tcpserver->close(); //关闭监听
    }
    //关联信号，当有新到的连接时，执行槽函数
    connect(tcpserver,SIGNAL(newConnection()),this,SLOT(createConnection()));
    readPassword();
    read();
}

void server::createConnection()
{
    QTcpSocket *newsocket = tcpserver->nextPendingConnection();
    all_socket.insert(std::make_pair(0, newsocket));
    connect(newsocket, SIGNAL(readyRead()), this, SLOT(readData()));
//    connect(newsocket, SIGNAL(disconnected()), this, SLOT(deleteLater()));
}

void server::readData()
{
    qDebug() << "server readdata" << "socket number " << all_socket.size();
    std::map<int, QTcpSocket*>::iterator iter;
    for(iter = all_socket.begin(); iter != all_socket.end(); iter++)
    {
        qDebug() << iter -> first << " ";
        QTcpSocket *one  = iter -> second;
        qDebug() << one -> bytesAvailable();
        if(one ->bytesAvailable() > 0)
        {
            QDataStream in(one);
            in.setVersion(QDataStream::Qt_4_6);
            blockSize =  one -> read(2).toInt();
            QString msg; in >> msg;
            qDebug() << "server recive data --- " << msg;
            QStringList list = msg.split(' ');
            switch(list[1].toInt())
            {
                case ChangePw: changePassword(list[0].toInt(), list[2]); break;
                case CheckPw: checkPassword(list[2].toInt(), list[3]); break;
                case AddCourse: addCourse(list[0].toInt(), list); break;
                case DelCourse: delCourse(list[0].toInt(), list[2].toInt()); break;
                case GetCourse: getCourse(list[0].toInt()); break;
                case GetDetail: getDetail(list[0].toInt(), list[2].toInt());break;
                case GetStudent: getStudent(list[0].toInt(), list[2].toInt()); break;
                case GetAllCourse: getAllCourse(list[0].toInt()); break;
                case ChangeScore: changeScore(list[0].toInt(), list[2].toInt(), list);
                case GetSelect: getSelectCourse(list[0].toInt());break;
                case GetOptional: getOptionalCourse(list[0].toInt());break;
                case disConnect: deletesocket(list[0].toInt());break;
                case sortFirst:SortFirst(list[0].toInt(), list[2].toInt());break;
                case sortSecond:SortSecond(list[0].toInt(), list[2].toInt());break;
            }
        }
    }
}

void server::sendData(int id, QString data)
{
    QByteArray block;
    QDataStream out(&block,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_6);
    out << (quint16) 0;
    out << QString::number(id) + " " + data;
    out.device() -> seek(0);
    out << (quint16) (block.size() - sizeof(quint16));
    qDebug() << "socket number" << " " << all_socket.size();
    if(all_socket.count(id))
    {
        qDebug() << "server send " << data;
        all_socket[id] -> write(block);
    }
}

person* server::findPerson(int person_id)
{
    foreach(person *one, all_person)
        if(one -> get_id() == person_id)return one;
    return nullptr;
}

//查找对应id的课程指针
course* server::findCourse(int course_id)
{
    foreach(course *one, all_course)
        if(one -> get_id() == course_id)return one;
    return nullptr;
}

//读取数据
void server::read()
{
    read("D:/QT/C++/StudentSystemNet/server/files/teacher.txt", true);
    read("D:/QT/C++/StudentSystemNet/server/files/student.txt", false);
//    read(":/files/teacher.txt", true);
//    read(":/files/student.txt", false);
}

//保存/更新数据
void server::write()
{
    write("D:/QT/C++/StudentSystemNet/server/files/teacher.txt", true);
    write("D:/QT/C++/StudentSystemNet/server/files/student.txt", false);
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

void server::read(QString filename, bool kind)
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

void server::write(QString filename, bool flag)
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

void server::checkPassword(int id, QString pw)
{
    //比较密码
    int ans = 0;
    if(!password.count(id))ans = -1;       //无此账号
    else if(password[id] != pw)ans = 0;         //密码错误
    else ans = 1;
    sendData(0, tr("1 ") + QString::number(ans));
    QTcpSocket *t = all_socket[0];
    all_socket.erase(0);
    if(ans == 1)
    {
        all_socket.insert(std::make_pair(id, t));
    }
}
void server::deletesocket(int id)
{
    write();
    writePassword();
    if(all_socket.count(id))
    {
        all_socket[id]->abort();
        all_socket.erase(id);
    }
}
void server::readPassword()
{
    password.clear();                                   //清空password map容器
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);

    try
    {
        QFile file("D:/QT/C++/StudentSystemNet/server/files/password.txt");
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
            throw QString(tr("can't open the file"));   //打开文件失败，抛出异常
        //读取id及对应密码
        while(!file.atEnd())
        {
            QByteArray line = file.readLine();
            QString _str(line);
            QStringList list = _str.remove("\n").split(" ");
            password.insert(std::make_pair(list[0].toInt(), list[1]));
        }
    }
    catch(QString e)                                    //捕获异常
    {
        QMessageBox::about(this, "Error!", e);
    }
}

void server::writePassword()
{
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);
    try
    {
        QFile file("D:/QT/C++/StudentSystemNet/server/files/password.txt");
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
            throw QString(tr("can't open the file"));
        QTextStream out(&file);
        std::map<int, QString>::iterator iter;
        for(iter = password.begin(); iter != password.end(); iter++)
        {
            out << iter -> first << " " << iter -> second;
            out << "\n";
        }
    }
    catch(QString e)
    {
        QMessageBox::about(this, "Error!", e);
    }
}

void server::changePassword(int id, QString newpw)
{
    password[id] = newpw;
}

void server::getCourse(int hostId)
{
    person *one = findPerson(hostId);
    QString msg = "2";
    std::map<int, int>::iterator iter;
    for(iter = one -> course_map.begin(); iter != one -> course_map.end(); iter++)
    {
        course *co = findCourse(iter -> first);
        msg += " " + QString::number(iter -> first) + " "
             + co -> get_name() + " "
             + QString::number(co -> get_credit()) + " ";
        msg += (co -> flag ? "1" : "0");
    }
    sendData(hostId, msg);
}

void server::getAllCourse(int id)
{
    QString msg = "6";
    foreach(course *co, all_course)
    {
        msg += " " + QString::number(co -> get_id()) + " "
             + co -> get_name() + " "
             + QString::number(co -> get_credit()) + " "
             + QString::number(co -> student_map.size()) + " ";
        msg += (co -> flag ? "1" : "0");
    }
    sendData(id, msg);
}

void server::getSelectCourse(int id)
{
    person *one = findPerson(id);
    QString msg = "4";
    std::map<int, int>::iterator iter;
    for(iter = one -> course_map.begin(); iter != one -> course_map.end(); iter++)
    {
        course *co = findCourse(iter -> first);
        msg += " " + QString::number(iter -> first) + " "
             + co -> get_name() + " "
             + QString::number(iter -> second) + " "
             + QString::number(co -> get_GPA(this, id)) + " ";
        msg += (co -> flag ? "1" : "0");
    }
    sendData(id, msg);
}

void server::getOptionalCourse(int id)
{
    person *one = findPerson(id);
    QString msg = "5";

    foreach(course *co, all_course)
    {
        if(!one -> course_map.count(co -> get_id()))
        {
            msg += " " + QString::number(co -> get_id()) + " "
                + co -> get_name() + " "
                + QString::number(co -> get_credit());
        }
    }
    sendData(id, msg);
}

void server::getStudent(int id, int course_id)
{
    course *co = findCourse(course_id);
    QString msg = "3 " + co -> get_name();
    std::map<int, int>::iterator iter;
    for(iter = co -> student_map.begin(); iter != co -> student_map.end(); iter++)
    {
        person *one = findPerson(iter -> first);
        msg += " " + QString::number(iter -> first) + " "
             + one -> get_name() + " "
             + QString::number(iter -> second);
    }
    sendData(id, msg);
}

void server::getDetail(int hostId, int id)
{
    person *one = findPerson(id);
    QString msg = "7 ";
    msg += QString::number(one -> get_id()) + " "
         + one -> get_name() + " "
         + QString::number(one -> get_class());
    sendData(hostId, msg);
}

void server::changeScore(int hostId, int course_Id, QStringList &list)
{
    int len = list.size();
    course *co = findCourse(course_Id);

    for(int i = 3; i < len; i += 2)
    {
        int student_id = list[i].toInt();
        int score = list[i+1].toInt();
        person *stu = findPerson(student_id);
        stu -> course_map[course_Id] = score;
        co -> student_map[student_id] = score;
    }
    getStudent(hostId, course_Id);

    for(int i = 3; i < len; i += 2)
    {
        getSelectCourse(list[i].toInt());
    }
}

void server::addCourse(int hostId, QStringList &list)
{
    int len = list.size();
    for(int i = 2; i < len; i++)
    {
        int CourseId = list[i].toInt();
        person *host = findPerson(hostId);
        host -> add(CourseId);
        course *ans = findCourse(CourseId);
        ans -> student_map.insert(std::make_pair(hostId, -1));
        int teacher_id = findTeacherOfCourse(CourseId);
        getStudent(teacher_id, CourseId);
    }
    getSelectCourse(hostId);
}
int server::findTeacherOfCourse(int course_id)
{
    foreach(person *one, all_person)
    {
        if(one -> flag && one -> course_map.count(course_id))
           return one -> get_id();
    }
}
void server::delCourse(int hostId, int CourseId)
{
    person *host = findPerson(hostId);
    course *ans = findCourse(CourseId);
    if(host -> flag)
    {
        std::map<int, int>::iterator iter;
        for(iter = ans -> student_map.begin(); iter != ans -> student_map.end(); iter++)
        {
            //有至少一位学生成绩已知则判断是否删除
            if(~iter -> second)
            {
                if(QMessageBox::question(this, "确认删除", "该课程学生成绩已经公布，确认删除?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
                {
                    host -> course_map.erase(CourseId);
                    break;
                }
                else
                    return;
            }
        }
        getCourse(hostId);
        foreach(person *p, all_person)
        {
            if(p -> course_map.count(CourseId) && !p->flag)
            {
                p -> course_map.erase(CourseId);
                getSelectCourse(p->get_id());
            }
        }
    }
    else
    {
        host -> del(CourseId);
        course *ans = findCourse(CourseId);
        ans -> student_map.erase(hostId);
        getSelectCourse(hostId);
        int teacher_id = findTeacherOfCourse(CourseId);
        getStudent(teacher_id, CourseId);
    }
}
std::vector<pair> server::SortFirst(int kind, int id)
{
//    排序
    std::map<int,int> _map = findCourse(id) ->student_map;
    switch(kind)
    {
        case first_up: return FirstUp(_map);
        case first_down:return FirstDown(_map);
        case second_up:return SecondUp(_map);
        case second_down:return SecondDown(_map);
    }
}
std::vector<pair> server::SortSecond(int kind, int id)
{
    std::map<int,int> _map = findPerson(id)->course_map;
    switch(kind)
    {
        case first_up: return FirstUp(_map);
        case first_down:return FirstDown(_map);
        case second_up:return SecondUp(_map);
        case second_down:return SecondDown(_map);
    }
    std::vector<pair> p;
    if(!findPerson(id) -> flag)
        getSelectCourse(id);
    else getCourse(id);
    return p;
}
void server::changeSortKind(int index)
{
    int kind = 0;
    if(index == 0)
        kind = (kind == first_down) ? first_up : first_down;
    else if(index == 2)
        kind =(kind == second_down) ? second_up : second_down;
}
server::~server()
{
    write();
    writePassword();
    std::map<int, QTcpSocket*>::iterator iter;
    for(iter = all_socket.begin(); iter != all_socket.end(); iter++)
    {
        delete iter -> second;
    }
    delete tcpserver;
}
