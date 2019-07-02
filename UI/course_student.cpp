#include <qDebug>
#include <QMessageBox>
#include "course_student.h"
course_student::course_student(int course_id, manage * _fa):
    childwidget(_fa)
{
    fa = _fa;
    id = course_id;
    setParent(_fa);
    setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    post = new QPushButton(tr("提交成绩"), this);
    post -> move(300, 300);
    connect(post, SIGNAL(clicked()), this, SLOT(post_clicked()));
    connect(table, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(getItem(int, int)));
    connect(table, SIGNAL(cellChanged(int, int)), this, SLOT(get_changeItem(int, int)));
    sendData(tr("8 ") + QString::number(id));
}

void course_student::update(QStringList &list)
{
//    设置行数列数
    disconnect(table, SIGNAL(cellChanged(int, int)), this, SLOT(get_changeItem(int, int)));

    int len  = list.length();
    table -> setRowCount(0);
    table->setRowCount((len-2) / 3);
    table->setColumnCount(3);
//    表头设置
    QStringList header;
    header << "学生编号" << "姓名" << "分数";
    table -> setHorizontalHeaderLabels(header);
    for(int i = 0, j = 3; j < len; i ++, j += 3)
    {
        table -> setItem(i, 0, new QTableWidgetItem(list[j]));
        table -> setItem(i, 1, new QTableWidgetItem(list[j+1]));
        table -> setItem(i, 2, new QTableWidgetItem());
        table -> item(i, 2) -> setData(Qt::DisplayRole, list[j+2].toInt());
        table -> item(i, 0) -> setTextAlignment(Qt::AlignCenter);
        table -> item(i, 1) -> setTextAlignment(Qt::AlignCenter);
        table -> item(i, 2) -> setTextAlignment(Qt::AlignCenter);
        table -> show();
    }
    connect(table, SIGNAL(cellChanged(int, int)), this, SLOT(get_changeItem(int, int)));
}
//获取点击位置
void course_student::getItem(int row, int col)
{
    if(row < table -> rowCount())
    {
        if(col == 1)        //查看学生信息
           emit sendData("6 " + table -> item(row, 0) -> text());
        else if(col == 2)   //更改成绩，先保存原来成绩
            tmp = table -> item(row, col) -> text().toInt();
    }
}
//获取修改位置
void course_student::get_changeItem(int row, int col)
{
    if(row < table -> rowCount() && col == 2)
    {
        try
        {
//      成绩格式不正确,抛出异常
            int score = table -> item(row, col) -> text().toInt();
            if(score < 0 || score > 100)throw QString(tr("分数格式错误。"));           
        }
//      捕获异常
        catch(QString e)
        {
            QMessageBox::about(this, "Error", e);
            table -> item(row, col) -> setData(Qt::DisplayRole, tmp);
        }
    }
}
//提交分数修改信息
void course_student::post_clicked()
{
    QString data = "";
    for(int i = 0; i < table -> rowCount(); i ++)
    {
        int score = table -> item(i, 2) -> text().toInt();
        data += " " + table -> item(i, 0) -> text() + " " + QString::number(score);
    }
    sendData("9 " + QString::number(id) + data);
}
