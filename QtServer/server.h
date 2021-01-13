#ifndef SERVER_H
#define SERVER_H

#include "user_manager.h"
#include "message_mananger.h"
#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>
#include <QTimer>
#include <QVector>
#include <QMap>
#include <QQueue>
namespace Ui {
    class server;
}

class Server : public QWidget
{
    Q_OBJECT

public:
    explicit Server(QWidget *parent = 0);
    ~Server();

private:
    QString getLocalIp();
    void printAllIp();
    bool userStatusUpdate();
    void handlemessage(QString myname, QTcpSocket *a);
    bool handleRequest(QStringList req,QTcpSocket *mSocket,qint32 userid);
    bool sendStatusToFriends(qint32 userid,bool status);
    bool sendAllUsersAndMessagesByid(qint32 userid,QTcpSocket *mSocket);
    bool sendUserMessagesByUserName(QString username,QString fusername,QString &str);
    bool getUserNameById(qint32 userid,QString &username);
    bool getUserStatusById(qint32 userid, bool &status);


private slots:
//自定义的槽函数
    void onNewConnection();            //QTcpServer 的 newConnect() 信号

private:
    const int Timeout=5*1000;
    UserManager *userManager;
    Ui::server *ui;
    QTcpServer *tcpServer; //监听
    messageManager *msgManager;
    QList<QTcpSocket*> tcpSockets; //通信
    QTimer timer;           //定时器
    QVector<qint32> mapUserid;//Socket对应的userid号码
    QMap<qint32,qint32> mapTcpSocket;//用户id向Socket的映射
    QQueue<qint32> pool;//未使用Socket下标
    QMap<qint32,userStatus> allUserStatus;//用户状态数组
};

#endif // SERVER_H
