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
    void post_pw(QString);      //向上层发送密码
    void cancel();
private slots:
    void on_confirm_clicked();  //确定按钮点击槽

    void on_reset_clicked();    //重置按钮点击槽

    void on_pushButton_clicked();//取消按钮点击槽

private:
    Ui::changepw *ui;
};

#endif // CHANGEPW_H
