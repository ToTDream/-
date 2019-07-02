#include <map>
#include <QDebug>
#include <qlabel.h>
#include <QPushButton>
#include "stu_selected.h"
stu_selected::stu_selected(int _id, manage *_fa):
    childwidget(_fa)
{
    fa = _fa;
    id = _id;
    setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    connect(this, SIGNAL(post_del_id(int)), fa, SLOT(delCourse(int)));
    connect(table, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(getItem(int, int)));
}

void stu_selected::update()
{
    table->setRowCount(0);
    table->setRowCount(fa -> one -> course_map.size());
    table->setColumnCount(5);


    QStringList header;                                                         //表头设置
    header << "课程编号" << "名称" << "分数" << "操作" << "绩点";
    table -> setHorizontalHeaderLabels(header);

    pair_vec vec = sort(fa -> one -> course_map);
    int i = 0;
    //填写表格
    foreach (pair iter, vec)
    {
        course *co = fa -> findCourse(iter.first);
        QTableWidgetItem *_id = new QTableWidgetItem(QString::number(iter.first));
        QTableWidgetItem *name = new QTableWidgetItem(co -> get_name());

        QTableWidgetItem *score = new QTableWidgetItem();
        score -> setData(Qt::DisplayRole, iter.second);

        QTableWidgetItem *gpa = new QTableWidgetItem();
        gpa -> setData(Qt::DisplayRole, fa -> findCourse(iter.first) -> get_GPA(fa, id));
        table -> setItem(i, 4, gpa);

        _id -> setTextAlignment(Qt::AlignCenter);
        name -> setTextAlignment(Qt::AlignCenter);
        score -> setTextAlignment(Qt::AlignCenter);
        if(co -> flag)                                                          //必修课背景颜色为黑色
        {
            _id -> setBackgroundColor(QColor(248, 248, 248));
            name -> setBackgroundColor(QColor(248, 248, 248));
            score -> setBackgroundColor(QColor(248, 248, 248));
        }
        table -> setItem(i, 0, _id);
        table -> setItem(i, 1, name);
        if(~iter.second)
        {
            table -> setItem(i, 2, score);
        }
        else
        {
            QTableWidgetItem *one = new QTableWidgetItem(tr("未知"));
            if(co -> flag)one -> setBackgroundColor(QColor(248, 248, 248));
            table -> setItem(i, 2, one);
            table -> item(i, 2) -> setTextAlignment(Qt::AlignCenter);
            if(!co -> flag)                                                    //为分数未知的选修课定义删除按钮
            {
                QLabel *label = new QLabel();
                label -> setText(tr("点击删除"));
                label -> setAlignment(Qt::AlignHCenter);
                table -> setCellWidget(i, 3, label);
            }
        }
//        table -> setItem(i, 4, new QTableWidgetItem(gpa));
        i++;
    }
    table -> show();
}
pair_vec stu_selected::sort(std::map<int,int> _map)
{
    switch(kind)
    {
        case first_up: return FirstUp(_map);
        case first_down:return FirstDown(_map);
        case second_up:return SecondUp(_map);
        case second_down:return SecondDown(_map);
    }
}
//修改排序类型
void stu_selected::changeSortKind(int index)
{
    if(index == 0)
        kind = (kind == first_down) ? first_up : first_down;
    else if(index == 2)
        kind =(kind == second_down) ? second_up : second_down;
    update();
}
//获取点击位置
void stu_selected::getItem(int row, int col)
{
    if(row >= table -> rowCount()) return;

    if(col == 3)
    {
        int course_id = table -> item(row, 0)->text().toInt();
        course *co = fa -> findCourse(course_id);

        if(!co -> flag && fa -> one -> course_map[course_id] == -1)             //删除课程
        emit post_del_id(table -> item(row, 0) -> text().toInt());
    }
    else if(col == 1)
       emit post_show_id(table -> item(row, 0) -> text().toInt());              //计算绩点
}
