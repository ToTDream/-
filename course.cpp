#include <cmath>
#include <QColor>
#include "course.h"
#include <QMessageBox>
course::course(int _id, int _credit, QString _name):
    id(_id), credit(_credit), name(_name)
{

}

int course::add(int id)
{
    student_map.insert(std::make_pair(id, -1));
}

require_course::require_course(int _id, int _credit, QString _name):
    course(_id, _credit, _name)
{
    flag = true;
}

float require_course::get_GPA(manage *fa, int student_id)
{

    int ans = 0, goal;
    std::map<int, int>::iterator iter;
    for(iter = student_map.begin(); iter != student_map.end(); iter++)
    {
        if(iter -> first == student_id)goal = iter -> second;
        ans += iter -> second;
    }
    try
    {
        if(ans == 0)throw QString("该必修课总成绩为0，无法计算绩点");
        return goal * 1.0 * credit / ans;

    }
    catch(QString exception)
    {
        QMessageBox::about(fa, "Error", exception);
    }
}


optional_course::optional_course(int _id, int _credit, QString _name):
     course(_id, _credit, _name)
{
    flag = false;
}

float optional_course::get_GPA(manage *fa, int student_id)
{
    std::map<int, int>::iterator iter;
    for(iter = student_map.begin(); iter != student_map.end(); iter++)
    {
        if(iter -> first == student_id)return sqrt(iter -> second) * credit / 10.0;
    }
}
