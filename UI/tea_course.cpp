#include <qDebug>
#include <QBoxLayout>
#include <QComboBox>
#include "tea_course.h"
tea_course::tea_course(int _id, manage *_fa):
    childwidget(_fa)
{
    setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    fa = _fa; id = _id;
    setParent(_fa);
    post = new QPushButton(tr("删除"), this);
    reset = new QPushButton(tr("重置"), this);
    post -> move(200, 300);
    reset -> move(300, 300);
    connect(post, SIGNAL(clicked()), this, SLOT(post_clicked()));
    connect(reset, SIGNAL(clicked()), this, SLOT(reset_clicked()));
    connect(this, SIGNAL(call_del_tab(int, QString)), fa, SLOT(delCourse(int, QString)));
    connect(this, SIGNAL(call_add_tab(int, QString)), fa, SLOT(add_course_Tab(int, QString)));
    connect(table, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(show_course_student(int, int)));
    sendData(tr("3 "));
}
//更新本窗口
void tea_course::update(QStringList& list)
{
    int len  = list.length();
    table -> setRowCount(0);
    table->setRowCount((len-2) / 4);
    table->setColumnCount(4);

    QStringList header;
    header << "课程编号" << "名称" << "学分" << "选择";
    table -> setHorizontalHeaderLabels(header);
    for(int i = 0, j = 2; j < len; i++, j += 4)
    {
        QTableWidgetItem *id = new QTableWidgetItem(list[j]);
        QTableWidgetItem *name = new QTableWidgetItem(list[j+1]);
        QTableWidgetItem *credit = new QTableWidgetItem(list[j+2]);
        id -> setTextAlignment(Qt::AlignCenter);
        name -> setTextAlignment(Qt::AlignCenter);
        credit -> setTextAlignment(Qt::AlignCenter);
        if(list[j+3].toInt())
        {
            id -> setBackgroundColor(QColor(248, 248, 248));
            name -> setBackgroundColor(QColor(248, 248, 248));;
            credit -> setBackgroundColor(QColor(248, 248, 248));;
        }
        table -> setItem(i, 0, id);
        table -> setItem(i, 1, name);
        table -> setItem(i, 2, credit);

        QTableWidgetItem *check = new QTableWidgetItem();
        check -> setCheckState(Qt::Unchecked);
        if(list[j+3].toInt())check -> setBackgroundColor(QColor(248, 248, 248));
        table -> setItem(i, 3, check);
    }
    table -> show();
}
//重置勾选信息
void tea_course::reset_clicked()
{
    for(int i = 0; i < table -> rowCount();i ++)
       table -> item(i, 3) -> setCheckState(Qt::Unchecked);
}
//提交删除信息
void tea_course::post_clicked()
{
    for(int i = 0; i < table -> rowCount(); i ++)
        if(table -> item(i, 3) -> checkState() == Qt::Checked)
        {
            emit call_del_tab(table -> item(i, 0) -> text().toInt(), table -> item(i, 1) -> text());
        }
}

void tea_course::show_course_student(int row, int col)
{
    if(row < table -> rowCount() && col == 1)
    {
        emit call_add_tab(table -> item(row, 0) -> text().toInt(), table -> item(row, 1) -> text());
    }
}
tea_course::~tea_course()
{
    delete post;
    delete reset;
}
