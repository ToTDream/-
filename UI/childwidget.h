#ifndef CHILDWIDGET_H
#define CHILDWIDGET_H
#include <QWidget>
#include <iostream>
#include "manage.h"
#include <QPushButton>
#include <QHeaderView>
#include <QTableWidget>

class manage;
class childwidget : public QWidget
{
    Q_OBJECT
public:
    explicit childwidget(manage *parent);
    ~childwidget();
    inline int get_id(){return id;}     //获取主人id
    virtual void update(QStringList &list);
protected:
    int id;                             //id
    manage *fa;                         //管理窗口指针
    QTableWidget *table;                //表格
    QPushButton *reset, *post;          //重置，提交按钮
signals:
    void sendData(QString);
    virtual void post_change_id(int);   //更改信号
public slots:
};

#endif // CHILDWIDGET_H
