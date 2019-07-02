#include <cmath>
#include <QColor>
#include "course.h"
#include <QMessageBox>
course::course(int _id, int _credit, QString _name):
    id(_id), credit(_credit), name(_name)
{
    student_map.clear();
}
//添加学生
void course::add(int id)
{
    student_map.insert(std::make_pair(id, -1));
}
//重载<<
QTextStream& operator <<(QTextStream &out, course &c)
{
    out << " " << c.get_id() << " " << c.get_name() << " " << c.get_credit() << " " << (c.flag ? "yes" : "no");
    return out;
}

require_course::require_course(int _id, int _credit, QString _name):
    course(_id, _credit, _name)
{
    flag = true;
}
//计算必修课GPA
float require_course::get_GPA(manage *fa, int student_id)
{
    try
    {
        int ans = 0, goal = 0;
        std::map<int, int>::iterator iter;
        for(iter = student_map.begin(); iter != student_map.end(); iter++)
        {
            if(iter -> first == student_id)goal = iter -> second;
            ans += iter -> second;
        }
        //总成绩为0，抛出异常
        if(ans == 0)throw QString("该必修课总成绩为0，无法计算绩点");
        //否则返回计算结果
        return goal * 1.0 * credit / ans;
    }
    catch(QString exception)
    {
        //捕获异常
        QMessageBox::about(fa, "Error", exception);
    }
}

optional_course::optional_course(int _id, int _credit, QString _name):
     course(_id, _credit, _name)
{
    flag = false;
}
//计算选修课GPA
float optional_course::get_GPA(manage *fa, int student_id)
{
    std::map<int, int>::iterator iter;
    for(iter = student_map.begin(); iter != student_map.end(); iter++)
    {
        if(iter -> first == student_id)return sqrt(iter -> second) * credit / 10.0;
    }
}
