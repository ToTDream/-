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
    post = new QPushButton(tr("提交成绩"), this);
    post -> move(300, 300);
    connect(this, SIGNAL(post_show_id(int)), fa, SLOT(showdetail(int)));
    connect(post, SIGNAL(clicked()), this, SLOT(post_clicked()));
    connect(table, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(getItem(int, int)));
    connect(table, SIGNAL(cellChanged(int, int)), this, SLOT(get_changeItem(int, int)));
    update();
}

void course_student::update()
{
//    设置行数列数
    disconnect(table, SIGNAL(cellChanged(int, int)), this, SLOT(get_changeItem(int, int)));
    table->setRowCount(0);
    table->setRowCount(cur_course->student_map.size());
    table->setColumnCount(3);
//    表头设置
    QStringList header;
    header << "学生编号" << "姓名" << "分数" << "绩点";
    table -> setHorizontalHeaderLabels(header);
//    向表中添加数据
    pair_vec vec = sort(cur_course -> student_map);
    int i = 0;
    foreach (pair iter, vec)    //填写表格
    {
        person *stu = fa -> findPerson(iter.first);
        table -> setItem(i, 0, new QTableWidgetItem(QString::number(iter.first)));
        table -> setItem(i, 1, new QTableWidgetItem(stu -> get_name()));

        table -> setItem(i, 2, new QTableWidgetItem());
        table -> item(i, 2) -> setData(Qt::DisplayRole, iter.second);
//        table -> setItem(i, 3, new QTableWidgetItem());
//        course *co = fa -> findCourse(cur_course -> get_id());
//        table -> item(i, 3) -> setData(Qt::DisplayRole, co -> get_GPA(fa, iter -> ));

        table -> item(i, 0) -> setTextAlignment(Qt::AlignCenter);
        table -> item(i, 1) -> setTextAlignment(Qt::AlignCenter);
        table -> item(i, 2) -> setTextAlignment(Qt::AlignCenter);
        table -> show();
        i++;
    }
    connect(table, SIGNAL(cellChanged(int, int)), this, SLOT(get_changeItem(int, int)));
}
//获取点击位置
void course_student::getItem(int row, int col)
{
    if(row < table -> rowCount())
    {
        if(col == 1)        //查看学生信息
           emit post_show_id(table -> item(row, 0) -> text().toInt());
        else if(col == 2)   //更改成绩，先保存原来成绩
            tmp = table -> item(row, col) -> text().toInt();
    }
}
//获取修改位置
void course_student::get_changeItem(int row, int col)
{
    if(row < table -> rowCount() && col == 2)
    {
        try
        {
            qDebug() << "item" << table -> item(row, col);
//              成绩格式不正确,抛出异常
            int score = table -> item(row, col) -> text().toInt();
            qDebug() << "score" << score;
            if(score < 0 || score > 100)throw QString(tr("分数格式错误。"));
        }
//              捕获异常
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
        emit post_change_id(table -> item(i, 0) -> text().toInt(), id, score);//发送修改信号
    }
}
