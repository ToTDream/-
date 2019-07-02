#ifndef STU_OPCTIONAL_H
#define STU_OPCTIONAL_H
#include "childwidget.h"

//学生可选的课程
class stu_optional:public childwidget
{
    Q_OBJECT
public:
    stu_optional(int, manage*);
    ~stu_optional();
    void update();
private:
    QPushButton *post, *reset;
signals:
private slots:
    void post_clicked();    //发送添加的课程id
    void reset_clicked();   //重置复选框按钮点击槽
};

#endif // STU_OPCTIONAL_H
