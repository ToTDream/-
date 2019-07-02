#ifndef CHILDWIDGET_H
#define CHILDWIDGET_H
#include <QWidget>
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
    virtual void update();
    inline int get_id(){return id;}
protected:
    int id;
    manage *fa;
    QTableWidget *table;
    QPushButton *reset, *post;
signals:
    virtual void post_del_id(int);
    virtual void post_change_id(int);
public slots:
};

#endif // CHILDWIDGET_H
