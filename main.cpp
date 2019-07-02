#include "mainwindow.h"
#include <QApplication>
#include <logindialog.h>
#include <QFile>
#include <QTextStream>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//  添加QSS样式

    QFile file(":/lightgray.qss");
    file.open(QFile::ReadOnly);
    QTextStream filetext(&file);
    QString stylesheet = filetext.readAll();
    a.setStyleSheet(stylesheet);
    file.close();

    MainWindow w;
    return a.exec();
}
