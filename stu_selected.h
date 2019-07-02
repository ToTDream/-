#ifndef STU_SELECTED_H
#define STU_SELECTED_H

#include "childwidget.h"
class stu_selected : public childwidget
{
   Q_OBJECT
public:
    stu_selected(int, manage*);
    void update();
signals:
    void post_del_id(int);
    void post_show_id(int);
private slots:
    void getItem(int, int);
};

#endif // STU_SELECTED_H
