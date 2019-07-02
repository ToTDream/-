#include "inquiredialog.h"
#include "ui_inquiredialog.h"

inquiredialog::inquiredialog(QString str, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::inquiredialog)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    ui -> label -> setText(str);
}

inquiredialog::~inquiredialog()
{
    delete ui;
}
