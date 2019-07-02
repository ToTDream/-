#include "childwidget.h"
#include <QTableWidget>
#include <QHeaderView>
#include <QDebug>
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
    QHeaderView *headerScore = table->horizontalHeader();
    headerScore -> setSortIndicator(0, Qt::AscendingOrder);
    headerScore -> setSortIndicatorShown(true);
    connect(headerScore, SIGNAL(sectionClicked(int)), table, SLOT (sortByColumn(int)));
}
void childwidget::update(QStringList& list)
{
    int len  = list.length();
    table -> setRowCount(0);
    table->setRowCount((len-2) / 5);
    table->setColumnCount(4);
    QStringList header;
    header << "课程编号" << "名称" << "学分" << "人数";                   //设置表头
    table -> setHorizontalHeaderLabels(header);
    for(int i = 0, j = 2; j < len; i++, j += 5)                             //向表格添加数据
    {
        QTableWidgetItem *id = new QTableWidgetItem(list[j]);
        QTableWidgetItem *name = new QTableWidgetItem(list[j+1]);
        QTableWidgetItem *credit = new QTableWidgetItem(list[j+2]);
        QTableWidgetItem *account = new QTableWidgetItem(list[j+3]);

        //必修课背景颜色改为灰色
        if(list[j+4].toInt())
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
        table -> setItem(i, 3, account);
    }
    table -> show();
}

childwidget::~childwidget()
{
    delete table;
}
