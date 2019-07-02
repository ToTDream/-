#include "stu_optional.h"
#include "manage.h"
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

void stu_optional::update(QStringList& list)
{
    int len  = list.length();
    table -> setRowCount(0);
    table->setRowCount((len-2) / 3);
    table->setColumnCount(4);

    QStringList header;                                             //表头设置
    header << "课程编号" << "名称" << "学分" << "选择";
    table -> setHorizontalHeaderLabels(header);    
    //填写表格
    for(int i = 0, j = 2; j < len; j += 3)
    {
            table -> setItem(i, 0, new QTableWidgetItem(list[j]));
            table -> setItem(i, 1, new QTableWidgetItem(list[j+1]));
            table -> setItem(i, 2, new QTableWidgetItem(list[j+2]));
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
    QString data = "3";
    for(int i = 0; i < table -> rowCount(); i ++)
    {
//      添加课程
        if(table -> item(i, 3) -> checkState() == Qt::Checked)
            data += " " +  table -> item(i, 0) -> text();
    }
    emit sendData(data);
}
stu_optional::~stu_optional()
{
    delete post;
    delete reset;
}

