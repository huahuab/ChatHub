#include "logindialog.h"
#include "ui_logindialog.h"
#include "registerdialog.h"
#include "clientwidget.h"
#include <QDebug>
#include <QtNetwork>
#include <QMessageBox>

LoginDialog::LoginDialog(quint16 cp, quint16 sp, QString ip, QTcpSocket **skt, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    client_port = cp;
    server_port = sp;
    this->ip = ip;
    socket = skt;
    ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_login_button_released()
{
    QString login = QString("1002 %1 %2").arg(ui->nameline->text()).arg(ui->pwdline->text());
    qDebug() << "login: " << login;
    if(ui->nameline->text().isEmpty() || ui->pwdline->text().isEmpty()) {
        QMessageBox::warning(this, "登陆失败", "请输入用户名和密码！", QMessageBox::Yes);
    }
    // 将账号和密码发送给服务器
    else {
        connectToServer(login);
    }

//    this->close();
}

void LoginDialog::on_register_button_released()
{
    RegisterDialog *reg = new RegisterDialog(tcpSocket);
    reg->exec();

}

void LoginDialog::pwdwrongSlot()
{
    QMessageBox::warning(this, "登录失败", "输入的账户名或密码有误，请重新尝试！", QMessageBox::Yes);
}

void LoginDialog::nonexSlot()
{
    QMessageBox::warning(this, "登录失败", "输入的账户名不存在，请重新尝试！", QMessageBox::Yes);
}

void LoginDialog::loginSuccessSlot()
{
    this->close();
}

void LoginDialog::connectToServer(QString login)
{
    tcpSocket = new QTcpSocket(this);
    *socket = tcpSocket;
    // if(tcpSocket == NULL) qDebug() << "login tcp invalid";
    emit tcp_signal();
    tcpSocket->abort();
    qDebug() << ip.toStdString().c_str();
    // 建立与服务器的连接
    tcpSocket->connectToHost(ip, server_port);
    if (tcpSocket->waitForConnected(2000))
    {
        qDebug() << "Successfully connected!";
        tcpSocket->write(login.toStdString().c_str());
        tcpSocket->waitForBytesWritten();
//        tcpSocket->flush();
    }
    else {
        qDebug() << "error in connecting";
        QMessageBox::warning(this, "连接失败", "无法连接到服务器", QMessageBox::Yes);
    }
}
