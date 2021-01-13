#include "server.h"
#include "ui_server.h"
#include <QByteArray>
#include <QMessageBox>
#include <QtNetwork>
#include <QTime>
#include <QPair>

Server::Server(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::server)
{
    ui->setupUi(this);
    userManager = new UserManager ;//用户管理类
    msgManager = new messageManager;//消息管理
    userManager->init("127.0.0.1","root","root","chathub");//初始化用户信息，改成加载配置文件
    if(!userManager->getUsersList(&allUserStatus)){//加载用户
        printf("Failed to get user status\n");
    }
    qDebug()<<"size:"<<allUserStatus.size();
    userStatusUpdate();//更新后端用户是否在线信息
    QTime t = QTime::currentTime();
    qsrand(t.msec()+t.second()*1000);
    //qDebug()<<"yonghu"<<userManager->checkUser("111","111");
    //qDebug()<<"charu"<<userManager->addUser("testj","testj");
    //QString localIp = getLocalIp();

    //设置UI显示界面相关信息
    printAllIp();
    setWindowTitle(QString("服务器端口：8888"));

    for(int i = 0 ;i < 20 ; i++ ){//创建连接线程池
        tcpSockets.push_back(new QTcpSocket(this));
        pool.enqueue(i);
        mapUserid.push_back(-1);
    }

    tcpServer = new QTcpServer(this);
    //绑定监听
    tcpServer->listen(QHostAddress::Any,8888);//监听所有IP的端口
    //有新连接，建立socket连接
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
}

Server::~Server()
{
    delete ui;
    delete userManager;
    delete tcpServer;
    delete msgManager;
}

void Server::onNewConnection()
{
    //获取通信套接字
    qint32 index;
    if(pool.isEmpty()){//队列为空，线程不够用了，加入新的连接
        index=tcpSockets.size();
        tcpSockets.push_back(new QTcpSocket(this));
        mapUserid.push_back(-1);
    }
    else {//取出一个连接
        index=pool.dequeue();
    }
//    QTcpSocket *tcpSockets[index]=tcpSockets[index];//更新当前线程下标
    qDebug()<<"socket id:"<<index<<endl;
    tcpSockets[index] = tcpServer->nextPendingConnection();//创建 socket
    if(!tcpSockets[index]->waitForConnected(Timeout))
    {
        qDebug()<<"连接失败!创建套接字失败!"<<endl;
        return;
    }

    //获取对方ip、port,输出连接信息到服务端窗口
    QString ip = tcpSockets[index]->peerAddress().toString().section(":",3,3);
    //QString ip = tcpSocket->peerAddress().toString();//获取IP，这样默认是IPV6地址
    quint16 port = tcpSockets[index]->peerPort();
    QString str = QString("[%1:%2]:成功连接").arg(ip).arg(port);
    ui->textBrowser->append(str);

    //处理各种网络请求
    connect(tcpSockets[index], &QTcpSocket::disconnected, this, [ = ] {//客户端断开
        QString str2 = QString("[%1:%2]:断开连接").arg(ip).arg(port);
        ui->textBrowser->append(str2);
        QMap<qint32,userStatus> ::iterator it=allUserStatus.find(mapUserid[index]);
        ui->textBrowser->append("用户"+it->username+"下线了！");
        it.value().status=false;
        //向在线好友发送下线消息;暂时没写;
        sendStatusToFriends(mapUserid[index],false);
        mapUserid[index]=-1;
        mapTcpSocket[mapUserid[index]]=-1;
        //qDebug()<<allUserStatus[mapUserid[index]].username;
        userStatusUpdate();
        tcpSockets[index]->deleteLater();
        pool.enqueue(index);
        msgManager->seedMessages();
    });
    connect(tcpSockets[index], &QTcpSocket::readyRead, this, [ = ]{//读取信息
        QByteArray buf = tcpSockets[index]->readAll();
        QString str2 = QString("[%1:%2]发送:").arg(ip).arg(port);
        ui->textBrowser->append(str2 + QString(buf));
        QStringList req = QString(buf).split(' ');//请求信息

        if(req[0]=="1002"){//登录请求,socket需要绑定id，直接完成响应
            if(req.size()>=3)
                qDebug()<<req[1]<<req[2]<<endl;
            QString ans;
            qint32 userid=-1;
            if(mapUserid[index]!=-1){
                qDebug()<<"重复登录"<<endl;
                ans="1002 103";
                //返回错误信息
            }
            else if(userManager->checkUser(req[1],req[2])){
                //保存socket和userid的映射关系
                userManager->getUseridByName(req[1],userid);
                qDebug()<<"登录成功"<<req[1]<<userid<<endl;
                mapTcpSocket[userid]=index;
                mapUserid[index]=userid;
                //设置在线状态
                QMap<qint32,userStatus> ::iterator it=allUserStatus.find(userid);
                ui->textBrowser->append("用户"+it->username+"上线了！");
                it.value().status=true;
                userStatusUpdate();
                ans="1002 0 ";
                User u;
                u.username=req[1];
                userManager->getUserInfoByUsername(u);
                ans+=u.nickname;
                ans+=" ";
                ans+=QString::number(u.userid);
                sendStatusToFriends(userid,true);
            }
            else{
                ans="1002 102";
            }
            msgManager->addMessage(new messageUnit(ans,userid,tcpSockets[index]));
            if(userid!=-1) sendAllUsersAndMessagesByid(userid,tcpSockets[index]);
        }
        else{//其余请求转去函数处理
            handleRequest(req,tcpSockets[index],mapUserid[index]);
        }
        msgManager->seedMessages();
    });
}

bool Server::handleRequest(QStringList req, QTcpSocket *mSocket, qint32 userid)
{
    if(req[0]=="1001"){
        QString ans="1001 101";
        qint32 newUserid;
        if(userManager->addUser(req[1],req[2],req[3],newUserid)){
            ans="1001 0";
        }
        msgManager->addMessage(new messageUnit(ans,userid,mSocket));
        allUserStatus.insert(newUserid,userStatus(req[1],false));
        userStatusUpdate();
    }
    else if(req[0]=="1005"){
        QString ans="1005 102";
        qint32 userid2;
        if(!userManager->getUseridByName(req[1],userid2))
            ;
        else if(userManager->makeFriendRelationshipInDB(userid,userid2)){
            ans="1005 0 ";
            ans+=QString::number(userid2);
            User u;
            u.username=req[1];
            userManager->getUserInfoByUsername(u);
            ans+=" ";
            ans+=u.nickname;
            userManager->init("127.0.0.1","root","root","chathub");//初始化用户信息，改成加载配置文件
        }
        msgManager->addMessage(new messageUnit(ans,userid,mSocket));
    }
    else if(req[0]=="1008"){
        QString ans="1008  105";
        QString username;
        getUserNameById(userid,username);
        if(userManager->modifyUserPasswordByUserName(username,req[1],req[2])){
            ans="1008 0";
        }
        msgManager->addMessage(new messageUnit(ans,userid,mSocket));
        userManager->init("127.0.0.1","root","root","chathub");
    }
    else if(req[0]=="1100"){
        qint32 targetid=req[2].toInt();
        QString chatmsg=req[1];
        if(userManager->saveChatMsgToDb(userid,targetid,chatmsg)){//消息存储成功，发送给接受者
            //1100 time+message sender-id
            QString ans="1100 ";
            QTime t = QTime::currentTime();
            ans+=" ";
            ans+=t.toString();
            ans+="\n";
            ans+=chatmsg;
            ans+=" ";
            ans+=QString::number(targetid);
            if(!mapTcpSocket.count(targetid)||mapTcpSocket[targetid]==-1){//不在线
                qDebug()<<"不在线，未离线消息"<<endl;
                return true;
            }
            msgManager->addMessage(new messageUnit(ans,targetid,tcpSockets[mapTcpSocket[targetid]]));
            qDebug()<<"消息转发成功";
        }
    }
    return true;
}

bool Server::sendStatusToFriends(qint32 userid, bool status)
{
    qDebug()<<"上下线通知:"<<endl;
    QList<friendInfo> fList;
    QString username;
    getUserNameById(userid,username);
    userManager->getFriendsListByUserName(username,fList);
    foreach(friendInfo f,fList){
        qDebug()<<mapTcpSocket.count(f.friendid);
        if(mapTcpSocket.count(f.friendid)&&mapTcpSocket[f.friendid]!=-1){//在线
            QString ans="1006 ";
            ans+=QString::number(userid);
            ans+=" ";
            ans+=QString::number(status);
            qDebug()<<"send:"<<ans<<endl;
            msgManager->addMessage(new messageUnit(ans,userid,tcpSockets[mapTcpSocket[f.friendid]]));
        }
    }
    return true;
}

bool Server::sendAllUsersAndMessagesByid(qint32 userid, QTcpSocket *mSocket)
{
    QList<friendInfo> fList;
    QString username,fusername;
    getUserNameById(userid,username);
    userManager->getFriendsListByUserName(username,fList);
    QString str;
    str+="1101 ";
    str+=QString::number(fList.size());
    foreach(friendInfo f,fList){
        str+=" ";
        str+=QString::number(f.friendid);
        str+=" ";
        getUserNameById(f.friendid,fusername);
        User u;
        u.username=fusername;
        userManager->getUserInfoByUsername(u);
        str+=u.nickname;
        str+=" ";
        bool status;
        getUserStatusById(f.friendid,status);
        str+=QString::number(status);
        sendUserMessagesByUserName(username,fusername,str);
        qDebug()<<"end";
    }
    qDebug()<<str<<endl;
    msgManager->addMessage(new messageUnit(str,userid,mSocket));
    return true;
}

bool Server::sendUserMessagesByUserName(QString username,QString fusername, QString &str)
{
    QList<Chatmsg> cList;
    userManager->getChatMsgFromDbByUsername(username,fusername,cList);
    str+=" ";
    str+=QString::number(cList.size());
    foreach(Chatmsg msg,cList)
    {
        str+=" ";
        str+=msg.msgtime;
        str+="\n";
        str+=msg.msgContent;
    }
    return true;
}

bool Server::getUserNameById(qint32 userid, QString &username)
{
    QMap<qint32,userStatus> ::iterator it=allUserStatus.find(userid);
    if(it==allUserStatus.end())
        return false;
    username=it.value().username;
    return true;
}

bool Server::getUserStatusById(qint32 userid, bool &status)
{
    QMap<qint32,userStatus> ::iterator it=allUserStatus.find(userid);
    if(it==allUserStatus.end())
        return false;
    status=it.value().status;
    return true;
}
QString Server::getLocalIp()
{
    QString hostName = QHostInfo::localHostName();
    QHostInfo hostInfo = QHostInfo::fromName(hostName);
    qDebug()<<("localHostName:" + hostName);
    foreach (QHostAddress addr, hostInfo.addresses()) {
        if (QAbstractSocket::IPv4Protocol == addr.protocol()) {
            return addr.toString();
        }
    }
    return QString();
}

void Server::printAllIp()
{
    ui->textBrowser->append("监听的地址:");
    QString localHostName = QHostInfo::localHostName();
    QHostInfo info = QHostInfo::fromName(localHostName);
    foreach(QHostAddress address,info.addresses()){
         if(address.protocol() == QAbstractSocket::IPv4Protocol){
            qDebug() << address.toString();
            ui->textBrowser->append(address.toString());
         }
    }
}

bool Server::userStatusUpdate()
{
    qDebug() << "用户状态更新,总用户数：";
    ui->le_usernum_off->clear();
    ui->le_usernum_on->clear();
    ui->tb_off->clear();
    ui->tb_on->clear();
    int num_on=0, num_off=0;
//    QString updatemessage = QString("load users' states##%1##").arg();
    for(QMap<qint32,userStatus> ::const_iterator it=allUserStatus.constBegin();it != allUserStatus.constEnd(); ++it)
    {
//        updatemessage = updatemessage.append(user.first);
        if(it.value().status) //在线
        {
            ui->tb_on->append(it.value().username);
            num_on++;
        }
        else
        {
            ui->tb_off->append(it.value().username);
            num_off++;
        }
    }
    ui->le_usernum_on->setText(QString::number(num_on, 10));
    ui->le_usernum_off->setText(QString::number(num_off, 10));
    return true;
}

