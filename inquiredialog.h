#ifndef INQUIREDIALOG_H
#define INQUIREDIALOG_H

#include <QDialog>

namespace Ui {
class inquiredialog;
}

class inquiredialog : public QDialog
{
    Q_OBJECT

public:
    explicit inquiredialog(QString, QWidget *parent = 0);
    ~inquiredialog();

private:
    Ui::inquiredialog *ui;
};

#endif // INQUIREDIALOG_H
