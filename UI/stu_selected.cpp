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

void stu_selected::update(QStringList& list)
{
    table -> horizontalHeader() -> sortIndicatorChanged(0,  Qt::AscendingOrder);
    qDebug() <<  table -> horizontalHeader() -> isSortIndicatorShown();
    int len  = list.length();
    table -> setRowCount(0);
    table->setRowCount((len-2) / 5);
    table->setColumnCount(5);
    QStringList header;
    header << "课程编号" << "名称" << "分数" << "绩点" << "操作";
    table -> setHorizontalHeaderLabels(header);
    //填写表格
    for(int i = 0, j = 2; j < len; i++, j += 5)
    {
        QTableWidgetItem *_id = new QTableWidgetItem(list[j]);
        QTableWidgetItem *name = new QTableWidgetItem(list[j+1]);
        QTableWidgetItem *score = new QTableWidgetItem();
        QTableWidgetItem *gpa = new QTableWidgetItem();
        _id -> setTextAlignment(Qt::AlignCenter);
        name -> setTextAlignment(Qt::AlignCenter);

        if(~list[j+2].toInt())
        {
            score -> setData(Qt::DisplayRole, list[j+2].toInt());
            gpa -> setText(list[j+3]);

        }
        else
        {
            score -> setText("未知");
            gpa -> setText("未知");
        }
        score -> setTextAlignment(Qt::AlignCenter);
        gpa -> setTextAlignment(Qt::AlignCenter);
        table -> setItem(i, 0, _id);
        table -> setItem(i, 1, name);
        table -> setItem(i, 2, score);
        table -> setItem(i, 3, gpa);

        if(list[j+4].toInt())                                                   //必修课背景颜色为黑色
        {
            _id -> setBackgroundColor(QColor(248, 248, 248));
            name -> setBackgroundColor(QColor(248, 248, 248));
            score -> setBackgroundColor(QColor(248, 248, 248));
            gpa ->  setBackgroundColor(QColor(248, 248, 248));
        }
        else
        {
            if(list[j+2].toInt() == -1)                                                    //为分数未知的选修课定义删除按钮
            {
                QLabel *label = new QLabel();
                label -> setText(tr("点击删除"));
                label -> setAlignment(Qt::AlignHCenter);
                table -> setCellWidget(i, 4, label);
            }
        }
    }
    table -> show();
    emit sendData("11");
}

//获取点击位置
void stu_selected::getItem(int row, int col)
{
    if(row >= table -> rowCount()) return;

    if(col == 4) //删除课程
    {
        emit sendData(tr("4 ") + table -> item(row, 0) -> text());
    }
}
