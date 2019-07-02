#include "childwidget.h"
#include <QTableWidget>
#include <QHeaderView>
#include <QDebug>
//子窗口基类
childwidget::childwidget(manage* _fa)
{
    fa = _fa;
    kind = first_down;
    table = new QTableWidget(this);
    table -> resize(440, 380);
    table -> resizeColumnsToContents();
    table -> resizeRowsToContents();
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);

    QHeaderView *headerview = table->horizontalHeader();
    headerview -> setSortIndicator(0, Qt::AscendingOrder);
    headerview -> setSortIndicatorShown(true);
    connect(headerview, SIGNAL(sectionDoubleClicked(int)), this, SLOT(changeSortKind(int)));

//    QHeaderView *headerScore = table->horizontalHeader();
//    headerScore -> setSortIndicator(2, Qt::AscendingOrder);
//    headerScore -> setSortIndicatorShown(true);
}
void childwidget::update()
{
    table->setRowCount(0);
    table->setRowCount(fa -> all_course.size());
    table->setColumnCount(4);

    QStringList header;
    header << "课程编号" << "名称" << "学分" << "人数";                   //设置表头
    table -> setHorizontalHeaderLabels(header);
    switch(kind)
    {
        case first_up: std::sort(fa -> all_course.begin(), fa -> all_course.end(), Id_Cmp_Up<course*>);break;
        case first_down: std::sort(fa -> all_course.begin(), fa -> all_course.end(), Id_Cmp_Down<course*>);break;
        case second_up: std::sort(fa -> all_course.begin(), fa -> all_course.end(), Score_Cmp_Up<course*>);break;
        case second_down: std::sort(fa -> all_course.begin(), fa -> all_course.end(), Score_Cmp_Down<course*>);break;
    }
    int i = 0;
    foreach(course *co, fa -> all_course)                               //向表格添加数据
    {
        QTableWidgetItem *id = new QTableWidgetItem(QString::number(co -> get_id()));
        QTableWidgetItem *name = new QTableWidgetItem(co -> get_name());
        QTableWidgetItem *credit = new QTableWidgetItem(QString::number(co -> get_credit()));
        QTableWidgetItem *account = new QTableWidgetItem(QString::number(co -> student_map.size()));

        //必修课背景颜色改为灰色
        if(co -> flag)
        {
            id -> setBackgroundColor(QColor(248, 248, 248));
            name -> setBackgroundColor(QColor(248, 248, 248));
            credit -> setBackgroundColor(QColor(248, 248, 248));
            account -> setBackgroundColor(QColor(248, 248, 248));
        }
        //中心对齐
        id -> setTextAlignment(Qt::AlignCenter);
        name -> setTextAlignment(Qt::AlignCenter);
        credit -> setTextAlignment(Qt::AlignCenter);
        account -> setTextAlignment(Qt::AlignCenter);
        table -> setItem(i, 0, id);
        table -> setItem(i, 1, name);
        table -> setItem(i, 2, credit);
        table -> setItem(i++, 3, account);
    }
    table -> show();
}
//排序
pair_vec childwidget::sort(std::map<int,int> _map)
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
void childwidget::changeSortKind(int index)
{
    if(index == 0)
        kind = (kind == first_down) ? first_up : first_down;
    else if(index == 2)
        kind =(kind == second_down) ? second_up : second_down;
    update();
}

childwidget::~childwidget()
{
    delete table;
}
