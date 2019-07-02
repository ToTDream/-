#ifndef STU_SELECTED_H
#define STU_SELECTED_H
#include "childwidget.h"

//学生已选的课程（包括所有必修课）
class stu_selected : public childwidget
{
   Q_OBJECT
public:
    stu_selected(int, manage*);
    void update();
    pair_vec sort(std::map<int,int>);
signals:
    void post_del_id(int);          //发送删除的课程id
    void post_show_id(int);         //发送要求显示GPA的课程id
private slots:
    void getItem(int, int);         //获取点击位置，并执行响应操作
    void changeSortKind(int);
};

#endif // STU_SELECTED_H
