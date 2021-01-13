#ifndef MESSAGE_MANANGER_H
#define MESSAGE_MANANGER_H

#include <QString>
#include <QList>
#include <QTcpSocket>
struct messageUnit
{
public:
    QString message;
    qint32 recvid; //接受者id
    QTcpSocket *mtcpScoket;
    messageUnit(QString msg, qint32 id,QTcpSocket *socket);
};

class messageManager
{
public:
    bool addMessage(messageUnit *message);
    bool seedMessages();
private:
    QList<messageUnit *> msgList;
};

#endif // MESSAGE_MANANGER_H
