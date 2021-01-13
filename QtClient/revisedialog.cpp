#include "revisedialog.h"
#include "ui_revisedialog.h"
#include <QMessageBox>

ReviseDialog::ReviseDialog(QTcpSocket *skt, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReviseDialog)
{
    tcpSocket = skt;
    ui->setupUi(this);
}

ReviseDialog::~ReviseDialog()
{
    delete ui;
}

void ReviseDialog::on_back_button_released()
{
    this->close();
}

void ReviseDialog::on_confirm_button_released()
{
    QString npwd = ui->new_line->text();
    QString opwd = ui->old_line->text();
    QString cpwd = ui->pwdconf_line->text();
    if(npwd.isEmpty() || opwd.isEmpty() || cpwd.isEmpty()) {
        QMessageBox::warning(this, "信息有误", "请填写表单的所有项目", QMessageBox::Yes);
    }
    else if(npwd != cpwd) {
        QMessageBox::warning(this, "信息有误", "两次输入的密码不一致", QMessageBox::Yes);
    }
    else {
        QString send = "1008 " + opwd + " " + npwd;
        tcpSocket->write(send.toStdString().c_str());
    }
}
