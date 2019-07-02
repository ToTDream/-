#include "mainwindow.h"
#include <QApplication>
#include <logindialog.h>
#include <QFile>
#include <QTextStream>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile file("D:/QT/C++/student_system(1)/QSS/lightgray.qss");
    file.open(QFile::ReadOnly);
    QTextStream filetext(&file);
    QString stylesheet = filetext.readAll();
    a.setStyleSheet(stylesheet);
    file.close();

    MainWindow w;
    return a.exec();
}
