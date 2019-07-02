#include <QFont>
#include <QFile>
#include <QDebug>
#include <fstream>
#include <QString>
#include <QPalette>
#include "manage.h"
#include <QTextStream>
#include <qtextcodec.h>
#include <QMessageBox>
manage::manage(QWidget *parent = nullptr)
{
    setWindowIcon(QIcon(":/images/main.jpg"));
    setWindowTitle(tr("教务管理系统"));
    showAllWidget = nullptr;
}

//重载>>,将数据由QStringlist读入到all_course中
void manage::showAllCourse()
{
    if(!showAllWidget) showAllWidget = new childwidget(this);
    emit MsendData(tr("8 "));
    showAllWidget -> show();
}

void manage::manageSend(QString msg)
{
    emit MsendData(msg);
}

manage::~manage()
{
    delete showAllWidget;
    showAllWidget = nullptr;
}
