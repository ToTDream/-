#ifndef STU_OPCTIONAL_H
#define STU_OPCTIONAL_H
#include "childwidget.h"
class stu_optional:public childwidget
{
    Q_OBJECT
public:
    stu_optional(int, manage*);
    void update();
private:
    QPushButton *post, *reset;
signals:
private slots:
    void post_clicked();
    void reset_clicked();
};

#endif // STU_OPCTIONAL_H
