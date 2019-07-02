#include "server.h"
#include <QApplication>
#include <QMessageBox>
#include <QTextCodec>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    server w;
    w.hide();
    return a.exec();
}
