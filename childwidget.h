#ifndef CHILDWIDGET_H
#define CHILDWIDGET_H
#include <QWidget>
#include <iostream>
#include "manage.h"
#include <QPushButton>
#include <QHeaderView>
#include <QTableWidget>
#include "sort_template.h"
enum sort_kind{first_up = 1, first_down, second_up, second_down, gpa_up, gpa_down};
typedef std::pair<int,int> pair;
typedef std::vector<pair> pair_vec;
class manage;
class childwidget : public QWidget
{
    Q_OBJECT
public:
    explicit childwidget(manage *parent);
    virtual void update();
    inline int get_id(){return id;}     //获取主人id
    ~childwidget();
protected:
    int id;                             //id
    manage *fa;                         //管理窗口指针
    sort_kind kind;                     //排序类型
    QTableWidget *table;                //表格
    QPushButton *reset, *post;          //重置，提交按钮
    pair_vec sort(std::map<int,int>);
signals:
    virtual void post_del_id(int);      //删除信号
    virtual void post_change_id(int);   //更改信号
public slots:
    virtual void changeSortKind(int);
};

#endif // CHILDWIDGET_H
