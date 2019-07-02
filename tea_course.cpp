#include <qDebug>
#include <QBoxLayout>
#include <QComboBox>
#include "tea_course.h"
#include "add_course.h"
tea_course::tea_course(int _id, manage *_fa):
    childwidget(_fa)
{
    setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    fa = _fa; id = _id;
    setParent(_fa);
    post = new QPushButton(tr("删除"), this);
    reset = new QPushButton(tr("重置"), this);
    addButton = new QPushButton(tr("点击添课"), this);
    post -> move(200, 300);
    reset -> move(300, 300);
    addButton -> move(100, 300);
    connect(addButton, SIGNAL(clicked()), this, SLOT(add()));
    connect(post, SIGNAL(clicked()), this, SLOT(post_clicked()));
    connect(reset, SIGNAL(clicked()), this, SLOT(reset_clicked()));
    connect(this, SIGNAL(call_del_tab(int)), fa, SLOT(delCourse(int)));
    connect(this, SIGNAL(call_add_tab(int)), fa, SLOT(add_course_Tab(int)));
    connect(table, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(show_course_student(int, int)));
    update();
}
//更新本窗口
void tea_course::update()
{
    table->setRowCount(0);
    table->setRowCount(fa -> one -> course_map.size());
    table->setColumnCount(4);

    QStringList header;
    header << "课程编号" << "名称" << "学分" << "选择";
    table -> setHorizontalHeaderLabels(header);

    pair_vec vec = sort(fa -> one -> course_map);
    int i = 0;
    foreach (pair iter, vec)    //填写表格
    {
        course *co = fa -> findCourse(iter.first);
        QTableWidgetItem *id = new QTableWidgetItem(QString::number(iter.first));
        QTableWidgetItem *name = new QTableWidgetItem(co -> get_name());
        QTableWidgetItem *credit = new QTableWidgetItem(QString::number(iter.second));
        id -> setTextAlignment(Qt::AlignCenter);
        name -> setTextAlignment(Qt::AlignCenter);
        credit -> setTextAlignment(Qt::AlignCenter);
        if(co -> flag)
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
        if(co -> flag)check -> setBackgroundColor(QColor(248, 248, 248));
        table -> setItem(i, 3, check);
        i++;
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
            emit call_del_tab(table -> item(i, 0) -> text().toInt());
        }
    update();
}
//添加课程
void tea_course::add()
{
    add_course *add_dialog = new add_course;
    add_dialog -> show();
    connect(add_dialog, SIGNAL(addcourse(int, QString, int, bool)), fa, SLOT(addCourse(int, QString, int, bool)));
    update();
}

void tea_course::show_course_student(int row, int col)
{
    if(row < table -> rowCount() && col == 1)
    {

        emit call_add_tab(table -> item(row, 0) -> text().toInt());
    }
}
tea_course::~tea_course()
{
    delete addButton;
    delete post;
    delete reset;
}
