#include "childwidget.h"
#include <QTableWidget>
#include <QHeaderView>

//子窗口基类
childwidget::childwidget(manage* _fa)
{
    fa = _fa;
    table = new QTableWidget(this);
    table -> resize(440, 380);
    table -> resizeColumnsToContents();
    table -> resizeRowsToContents();
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);

    QHeaderView *headerId = table->horizontalHeader();
    //SortIndicator为水平标题栏文字旁边的三角指示器
    headerId -> setSortIndicator(0, Qt::AscendingOrder);
    headerId -> setSortIndicatorShown(true);
    connect(headerId, SIGNAL(sectionClicked(int)), table, SLOT (sortByColumn(int)));

    QHeaderView *headerScore = table->horizontalHeader();
    //SortIndicator为水平标题栏文字旁边的三角指示器
    headerScore -> setSortIndicator(2, Qt::AscendingOrder);
    headerScore -> setSortIndicatorShown(true);
    connect(headerScore, SIGNAL(sectionClicked(int)), table, SLOT (sortByColumn(int)));
}
void childwidget::update()
{
    table->setRowCount(0);
    table->setRowCount(fa -> all_course.size());
    table->setColumnCount(4);

    QStringList header;
    header << "课程编号" << "名称" << "学分" << "人数";
    table -> setHorizontalHeaderLabels(header);

    int i = 0;
    foreach(course *co, fa -> all_course)
    {
        QTableWidgetItem *id = new QTableWidgetItem(QString::number(co -> get_id()));
        QTableWidgetItem *name = new QTableWidgetItem(co -> get_name());
        QTableWidgetItem *credit = new QTableWidgetItem(QString::number(co -> get_credit()));
        QTableWidgetItem *account = new QTableWidgetItem(QString::number(co -> student_map.size()));
        if(co -> flag)
        {
            id -> setBackgroundColor(QColor(248, 248, 248));
            name -> setBackgroundColor(QColor(248, 248, 248));
            credit -> setBackgroundColor(QColor(248, 248, 248));
            account -> setBackgroundColor(QColor(248, 248, 248));
        }
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
