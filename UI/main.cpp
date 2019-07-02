#include <QFile>
#include <QApplication>
#include <QTextStream>
#include "mainwindow.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile file("D:/QT/C++/StudentSystemNet/UI/lightgray.qss");
    file.open(QFile::ReadOnly);
    QTextStream filetext(&file);
    QString stylesheet = filetext.readAll();
    a.setStyleSheet(stylesheet);
    file.close();

    MainWindow w;
    w.hide();
    return a.exec();
}
