#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QString>
#include <QtNetwork>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(quint16 cp, quint16 sp, QString ip, QTcpSocket **skt, QWidget *parent = nullptr);
    ~LoginDialog();

    quint16 client_port;
    quint16 server_port;
    QString ip;

private slots:
    void on_login_button_released();

    void on_register_button_released();

    void pwdwrongSlot();

    void nonexSlot();

    void loginSuccessSlot();

signals:
    void tcp_signal();

    void login_signal(QString login);

private:
    Ui::LoginDialog *ui;

    void connectToServer(QString login);

    QTcpSocket *tcpSocket;
    QTcpSocket **socket;

};

#endif // LOGINDIALOG_H
