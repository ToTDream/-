#include <qDebug>
#include "person.h"
#include <QMessageBox>
#include "course_student.h"
course_student::course_student(int course_id, manage * _fa):
    childwidget(_fa)
{
    fa = _fa;
    id = course_id;
    setParent(_fa);
    cur_course = fa -> findCourse(id);
    setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    connect(this, SIGNAL(post_show_id(int)), fa, SLOT(showdetail(int)));
    connect(table, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(getItem(int, int)));
    post = new QPushButton(tr("提交成绩"), this);
    post -> move(300, 300);
    connect(post, SIGNAL(clicked()), this, SLOT(post_clicked()));
    update();
    connect(table, SIGNAL(cellChanged(int, int)), this, SLOT(get_changeItem(int, int)));
}

void course_student::update()
{
    table->setRowCount(0);
    table->setRowCount(cur_course->student_map.size());
    table->setColumnCount(3);

    QStringList header;
    header << "学生编号" << "姓名" << "分数";
    table -> setHorizontalHeaderLabels(header);

    int i = 0;
    std::map<int, int>::iterator iter;
    for(iter = cur_course -> student_map.begin(); iter != cur_course -> student_map.end(); iter++, i++)
    {
        person *stu = fa -> findPerson(iter -> first);
        table -> setItem(i, 0, new QTableWidgetItem(QString::number(iter -> first)));
        table -> setItem(i, 1, new QTableWidgetItem(stu -> get_name()));

        table -> setItem(i, 2, new QTableWidgetItem());
        table -> item(i, 2) -> setData(Qt::DisplayRole, iter -> second);

        table -> item(i, 0) -> setTextAlignment(Qt::AlignCenter);
        table -> item(i, 1) -> setTextAlignment(Qt::AlignCenter);
        table -> item(i, 2) -> setTextAlignment(Qt::AlignCenter);
        table -> show();
    }
}
//获取点击位置
void course_student::getItem(int row, int col)
{
    if(row < table -> rowCount())
        if(col == 1)
        {
           emit post_show_id(table -> item(row, 0) -> text().toInt());
        }
        else if(col == 2)
        {
            tmp = table -> item(row, col) -> text().toInt();
        }

}
//获取修改位置
void course_student::get_changeItem(int row, int col)
{
    qDebug() << "get_changeItem";
    if(row < table -> rowCount() && col == 2)
    {
        try
        {
            int score = table -> item(row, col) -> text().toInt();
            qDebug() << score;
            if(score <= 0)throw QString(tr("分数格式错误。"));
        }
        catch(QString e)
        {
            QMessageBox::about(this, "Error", e);
            table -> item(row, col) -> setData(Qt::DisplayRole, tmp);
        }
    }
}
//提交分数修改信息
void course_student::post_clicked()
{
    for(int i = 0; i < table -> rowCount(); i ++)
    {
        int score = table -> item(i, 2) -> text().toInt();
        emit post_change_id(table -> item(i, 0) -> text().toInt(), id, score);
    }
}
