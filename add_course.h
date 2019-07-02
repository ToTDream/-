#ifndef ADD_COURSE_H
#define ADD_COURSE_H

#include <QDialog>
#include <QButtonGroup>
namespace Ui {
class add_course;
}

class add_course : public QDialog
{
    Q_OBJECT

public:
    explicit add_course(QWidget *parent = 0);
    ~add_course();

private slots:
    void on_addButton_clicked();
    void on_resetButton_clicked();
signals:
    void addcourse(int, QString, int, bool);
private:
    Ui::add_course *ui;
    QButtonGroup *radiogroup;

};

#endif // ADD_COURSE_H
