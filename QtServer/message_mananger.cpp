#include "message_mananger.h"

messageUnit::messageUnit(QString msg, qint32 id, QTcpSocket *socket)
{
    message=msg;
    recvid=id;
    mtcpScoket=socket;
}

bool messageManager::addMessage(messageUnit *message)
{
    msgList.push_back(message);
    qDebug()<<"添加消息成功";
    return true;
}

bool messageManager::seedMessages()
{
    for(QList<messageUnit *>::Iterator msg=msgList.begin();msg!=msgList.end();msg++)
    {
        (*msg)->mtcpScoket->write((*msg)->message.toUtf8());
        (*msg)->mtcpScoket->flush();
        msgList.erase(msg);
    }
}
