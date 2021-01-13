#include "registerdialog.h"
#include "ui_registerdialog.h"
#include <QMessageBox>
#include <QDebug>

RegisterDialog::RegisterDialog(QTcpSocket *skt, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterDialog)
{
    tcpSocket = skt;
    ui->setupUi(this);
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::on_back_button_released()
{
    this->close();
}

void RegisterDialog::on_confirm_button_released()
{
    QString uname = ui->name_line->text();
    QString nick = ui->nick_line->text();
    QString pwd = ui->pwd_line->text();
    QString conf_pwd = ui->pwdconf_line->text();
    if(uname.isEmpty() || nick.isEmpty()
            || pwd.isEmpty() || conf_pwd.isEmpty()) {
        QMessageBox::warning(this, "信息有误", "请填写表单的所有项目", QMessageBox::Yes);
    }
    else if(pwd != conf_pwd) {
        QMessageBox::warning(this, "信息有误", "两次填写的密码不一样", QMessageBox::Yes);
    }
    else {
        qDebug() << "Registering";

        QString send = "1001 "+uname+" "+nick+" "+pwd;
        qDebug() << send;
        tcpSocket->write(send.toStdString().c_str());
    }
}
