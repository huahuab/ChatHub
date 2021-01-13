#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include <QWidget>
#include <QMap>
#include "logindialog.h"
#include "adddialog.h"
#include "registerdialog.h"
#include "revisedialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ClientWidget; }
QT_END_NAMESPACE

class ClientWidget : public QWidget
{
    Q_OBJECT

public:
    ClientWidget(QWidget *parent = nullptr);
    ~ClientWidget();

    bool isLogged();

    void dealLogin(QString info);
    void dealAll(QString info);
    void dealMessage(QString info);
    void dealRegister(QString info);
    void dealRevise(QString info);
    void dealAdd(QString info);
    void dealOnline(QString info);

public slots:
    void connectSlot();

    void initInfo(QString info);

    void onConnected();

    void readError(QAbstractSocket::SocketError);

    void readData();

private slots:
    void on_exit_button_released();

    void on_friend_list_cellClicked(int row, int column);

    void on_clear_button_released();

    void on_add_button_released();

    void on_revise_button_released();

    void on_send_button_released();

signals:
    void pwdwrong_signal();
    void nonex_signal();
    void login_success_signal();

    void add_success_signal();
    void add_error_signal();

private:
    Ui::ClientWidget *ui;

    LoginDialog *login;
    AddDialog *add;
    RegisterDialog *regist;
    ReviseDialog *revise;

    quint16 client_port;
    quint16 server_port;
    QString ip;
    QTcpSocket *tcpSocket;
    bool islogged;

    QString id;
    QString nickname;

    QMap<QString, QString> mNick; // ID -> Nickname
    QMap<QString, QString> mNid; // Nickname -> ID
    QMap<QString, int> mRow; // ID -> row
    QMap<int, QString> mId; // row -> ID
    QMap<QString, QVector<QString> > chats; // ID -> chat record

};
#endif // CLIENTWIDGET_H
