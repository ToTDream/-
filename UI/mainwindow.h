#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <list>
#include <QMainWindow>
#include "client.h"
#include "logindialog.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    std::list<client*> all_client;
    Ui::MainWindow *ui;
private slots:
    void add_User();
};

#endif // MAINWINDOW_H
