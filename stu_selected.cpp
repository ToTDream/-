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
    table->setColumnCount(4);

    QStringList header;
    header << "课程编号" << "名称" << "分数" << "操作";
    table -> setHorizontalHeaderLabels(header);

    int i = 0;
    std::map<int, int>::iterator iter;
    for(iter = fa -> one -> course_map.begin(); iter != fa -> one -> course_map.end(); iter++, i++)
    {
        course *co = fa -> findCourse(iter -> first);
        QTableWidgetItem *id = new QTableWidgetItem(QString::number(iter -> first));
        QTableWidgetItem *name = new QTableWidgetItem(co -> get_name());

        QTableWidgetItem *score = new QTableWidgetItem();
        score -> setData(Qt::DisplayRole, iter -> second);

        id -> setTextAlignment(Qt::AlignCenter);
        name -> setTextAlignment(Qt::AlignCenter);
        score -> setTextAlignment(Qt::AlignCenter);
        if(co -> flag)
        {
            id -> setBackgroundColor(QColor(248, 248, 248));
            name -> setBackgroundColor(QColor(248, 248, 248));
            score -> setBackgroundColor(QColor(248, 248, 248));
        }
        table -> setItem(i, 0, id);
        table -> setItem(i, 1, name);
        if(~iter -> second)
        {
            table -> setItem(i, 2, score);
        }
        else
        {
            QTableWidgetItem *one = new QTableWidgetItem(tr("未知"));
            if(co -> flag)one -> setBackgroundColor(QColor(248, 248, 248));
            table -> setItem(i, 2, one);
            table -> item(i, 2) -> setTextAlignment(Qt::AlignCenter);
            if(!co -> flag)
            {
                QLabel *label = new QLabel();
                label -> setText(tr("点击删除"));
                label -> setAlignment(Qt::AlignHCenter);
                table -> setCellWidget(i, 3, label);
            }
        }
    }
    table -> show();
}
//获取点击位置
void stu_selected::getItem(int row, int col)
{
    if(row >= table -> rowCount()) return;

    if(col == 3)
    {
        int course_id = table -> item(row, 0)->text().toInt();
        course *co = fa -> findCourse(course_id);

        if(!co -> flag && fa -> one -> course_map[course_id] == -1)
        emit post_del_id(table -> item(row, 0) -> text().toInt());
    }
    else if(col == 1)
       emit post_show_id(table -> item(row, 0) -> text().toInt());
}
