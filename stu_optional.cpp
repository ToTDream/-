#include "stu_optional.h"
#include "manage.h"
#include "person.h"
#include <QDebug>
stu_optional::stu_optional(int _id, manage *_fa):
    childwidget(_fa)
{
    setParent(_fa);
    fa = _fa; id = _id;
    setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);

    post = new QPushButton(tr("提交"), this);
    reset = new QPushButton(tr("重置"), this);
    post -> move(200, 300);
    reset -> move(300, 300);

    connect(post, SIGNAL(clicked()), this, SLOT(post_clicked()));
    connect(reset, SIGNAL(clicked()), this, SLOT(reset_clicked()));
}

void stu_optional::update()
{
    table->setRowCount(0);
    table->setRowCount(fa -> all_course.size() - fa -> one -> course_map.size());
    table->setColumnCount(4);

    QStringList header;                                             //表头设置
    header << "课程编号" << "名称" << "学分" << "选择";
    table -> setHorizontalHeaderLabels(header);    

    int i = 0;                                                      //填写表格
    switch(kind)
    {
        case first_up: std::sort(fa -> all_course.begin(), fa -> all_course.end(), Id_Cmp_Up<course*>);break;
        case first_down: std::sort(fa -> all_course.begin(), fa -> all_course.end(), Id_Cmp_Down<course*>);break;
        case second_up: std::sort(fa -> all_course.begin(), fa -> all_course.end(), Score_Cmp_Up<course*>);break;
        case second_down: std::sort(fa -> all_course.begin(), fa -> all_course.end(), Score_Cmp_Down<course*>);break;
    }
    foreach(course * course_one, fa -> all_course)
    {
        if(!fa -> one -> course_map.count(course_one -> get_id()))
        {
            table -> setItem(i, 0, new QTableWidgetItem(QString::number(course_one -> get_id())));
            table -> setItem(i, 1, new QTableWidgetItem(course_one -> get_name()));
            table -> setItem(i, 2, new QTableWidgetItem(QString::number(course_one -> get_credit())));
            table -> item(i, 0) -> setTextAlignment(Qt::AlignCenter);
            table -> item(i, 1) -> setTextAlignment(Qt::AlignCenter);
            table -> item(i, 2) -> setTextAlignment(Qt::AlignCenter);
                                                                    //插入复选框
            QTableWidgetItem *check = new QTableWidgetItem();
            check -> setCheckState(Qt::Unchecked);
            check -> setBackgroundColor(QColor(248, 248, 248));
            table -> setItem(i, 3, check);
            table -> item(i, 3) -> setWhatsThis(tr("勾选后点击提交可选课"));
            i++;
        }
    }
    table -> show();
}
//重置勾选信息
void stu_optional::reset_clicked()
{
    for(int i = 0; i < table -> rowCount();i ++)
       table -> item(i, 3) -> setCheckState(Qt::Unchecked);
}
//提交选课信息
void stu_optional::post_clicked()
{
    for(int i = 0; i < table -> rowCount(); i ++)
    {
//        添加课程
        if(table -> item(i, 3) -> checkState() == Qt::Checked)
        {
            fa -> one -> course_map.insert(std::make_pair(table -> item(i, 0) -> text().toInt(), -1));
        }
    }
    fa -> updatewidget();
}
stu_optional::~stu_optional()
{
    delete post;
    delete reset;
}

