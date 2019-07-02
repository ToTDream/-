#ifndef CHANGEPW_H
#define CHANGEPW_H

#include <QDialog>

namespace Ui {
class changepw;
}

class changepw : public QDialog
{
    Q_OBJECT

public:
    changepw(QWidget *parent = 0);
    ~changepw();
signals:
    void post_pw(QString);
    void cancel();
private slots:
    void on_confirm_clicked();

    void on_reset_clicked();

    void on_pushButton_clicked();

private:
    Ui::changepw *ui;
};

#endif // CHANGEPW_H
