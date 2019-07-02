#ifndef MANAGE_H
#define MANAGE_H

#include <map>
#include <vector>
#include <QWidget>
#include <QStringlist>
#include "childwidget.h"
#include <QtNetwork/QTcpSocket>

class childwidget;
class manage : public QWidget
{
    Q_OBJECT
public:
    explicit manage(QWidget*);
    virtual void updatewidget(){}               //更新窗口
    ~manage();
    virtual void updatewidget(QStringList &){}
    virtual void updatewidget(QStringList &, bool){}
    virtual void updatewidget(QStringList &, bool, QString){}
    childwidget *showAllWidget;
    int id;
protected:
private:
    QTcpSocket *tcpSocket;
signals:
    void postAddCourse(QString);
    void postDelCourse(QString);
    void MsendData(QString);
public slots:
    void showAllCourse();                        //显示所有课程
    virtual void manageSend(QString);
    virtual void delCourse(int){}                //删除课程
    virtual void addCourse(int){}                //添加课程
    virtual void showdetail(QStringList&){}      //显示详细信息
};



#endif // MANAGE_H
