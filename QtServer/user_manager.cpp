#include "user_manager.h"
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QString>
#include <QApplication>

userStatus::userStatus(QString name, bool s)
{
    username=name;
    status=s;
}

bool User::operator<(const User &user) const
{
    return username<user.username;
}

UserManager::UserManager(){
    ;
}

UserManager::~UserManager(){
    ;
}

bool UserManager::init(const char* dbServer, const char* dbUserName, const char* dbPassword, const char* dbName)
{
    m_strDbServer = dbServer;
    m_strDbUserName = dbUserName;
    if (dbPassword != NULL)
        m_strDbPassword = dbPassword;
    m_strDbName = dbName;
    qDebug()<<m_strDbServer<<m_strDbUserName<<m_strDbPassword<<m_strDbName<<endl;
    //从数据库中加载所有用户信息
    if (!loadUsersFromDb()){
        printf("Load user information failed!\n");
        return false;
    }
    //加载所有用户的好友信息,放在加载用户信息中了
//    for (set<User>::iterator it = m_allCachedUsers.begin();it!=m_allCachedUsers.end();++it)
//    {
//        if (!loadRelationshipFromDb(it->userid, *it->friends))
//        {
//            printf("Load relationship from db error, userid: %d\n", it->userid);
//            continue;
//        }
//    }
    return true;
}

bool UserManager::getUsersList(QMap<qint32,userStatus> *alluserStatus)
{
    qDebug()<<m_allCachedUsers.size();
    foreach(User user,m_allCachedUsers){
        alluserStatus->insert(user.userid,userStatus(user.username,false));
//        qDebug()<<user.userid;
    }
    return true;
}

bool UserManager::checkUser(QString username, QString password)
{
    User user;
    user.username=username;
    auto it=m_allCachedUsers.lower_bound(user);
    if(it->password==password) return true;
    qDebug()<<"用户名或密码错误"<<endl;
    return false;
}

bool UserManager::getUseridByName(const QString &username, qint32 &userid)
{
    User user;
    user.username=username;
    auto it=m_allCachedUsers.lower_bound(user);
    if(it->username!=username){
        qDebug()<<"通过用户名查询id失败"<<endl;
        return false;
    }
    else {
        userid=it->userid;
//        qDebug()<<it->userid<<userid;
    }
    return true;
}

bool UserManager::addUser(QString username, QString nickname,QString password,qint32 &userid)
{
    QSqlDatabase dbChatHub=connecToDb();
    QSqlQuery queryChatHub=QSqlQuery(dbChatHub);
    ++ m_baseUserId;
    QString sql = QString("INSERT INTO t_user(f_user_id, f_username, f_nickname, f_password, f_register_time) VALUES(%1, '%2', '%3', '%4', NOW())").arg(m_baseUserId).arg(username).arg(nickname).arg(password);
    if (!queryChatHub.exec(sql))
    {
        qDebug()<<"insert user error, sql: %s"<<sql;
        return false;
    }
    //设置一些字段的默认值
    User user;
    user.username=username;
    user.password=password;
    user.nickname=username;
    user.userid = m_baseUserId;
    user.facetype = 0;
    user.birthday = 19900101;
    user.gender = 0;
    user.ownerid = 0;
    {
        std::lock_guard<std::mutex> guard(m_mutex);
        m_allCachedUsers.insert(user);
    }
    userid=user.userid;
    return true;
}

bool UserManager::makeFriendRelationshipInDB(qint32 smallUserid, qint32 greaterUserid)
{
        if (smallUserid == greaterUserid)
            return false;
        if (smallUserid > greaterUserid)
            swap(smallUserid,greaterUserid);
        QSqlDatabase dbChatHub=connecToDb();
        QSqlQuery queryChatHub=QSqlQuery(dbChatHub);
        QString sql = QString("INSERT INTO t_user_relationship(f_user_id1, f_user_id2) VALUES(%1, %2)").arg(smallUserid).arg(greaterUserid);
        if (!queryChatHub.exec(sql))
        {
            qDebug()<<"make relationship error, smallUserid=" << smallUserid << ", greaterUserid=" << greaterUserid;
            return false;
        }
        qDebug()<<"make relationship sucess, smallUserid=" << smallUserid << ", greaterUserid=" << greaterUserid;
        return true;
}

bool UserManager::modifyUserPasswordByUserName(const QString &username, const QString &oldPassword, const QString &newPassword)
{
    User user;
    user.username=username;
    auto it=m_allCachedUsers.lower_bound(user);
    if(it->password!=oldPassword) {
        return false;
        qDebug()<<username<<"修改密码失败，旧密码错误！"<<endl;
    }
    QSqlDatabase dbChatHub=connecToDb();
    QSqlQuery queryChatHub=QSqlQuery(dbChatHub);
    QString sql = QString("UPDATE `t_user` SET `f_password` = '%1' WHERE (`f_user_id` = '%2');").arg(newPassword).arg(user.userid);
    if (!queryChatHub.exec(sql))
    {
        qDebug()<<username<<"修改密码失败！"<<endl;
        return false;
    }
    qDebug()<<username<<"修改密码成功！"<<endl;
    return true;
}

bool UserManager::getChatMsgFromDbByUsername(QString username,QString fusername,QList<Chatmsg> &cList)
{
    User user1;
    user1.username=username;
    auto it=m_allCachedUsers.lower_bound(user1);
    if(it->username!=username){
        qDebug()<<"通过用户名查询聊天信息失败"<<endl;
        return false;
    }
    else user1=*it;
    User user2;
    user2.username=fusername;
    it=m_allCachedUsers.lower_bound(user2);
    if(it->username!=fusername){
        qDebug()<<"通过用户名查询聊天信息失败"<<endl;
        return false;
    }
    else user2=*it;
    QSqlDatabase dbChatHub=connecToDb();
    QSqlQuery queryChatHub=QSqlQuery(dbChatHub);
    QString sql = QString("SELECT f_senderid, f_targetid, f_msgcontent, f_create_time FROM t_chatmsg WHERE (f_senderid = %1 AND f_targetid = %2) OR (f_senderid = %3 AND f_targetid = %4) ORDER BY f_create_time").arg(user1.userid).arg(user2.userid).arg(user2.userid).arg(user1.userid);
//    qDebug()<<"获取消息"<<sql;
    if(!queryChatHub.exec(sql))//查询失败抛出异常
    {
        return false;
    }
    while(queryChatHub.next())//一行一行遍历，取出当前行的内容,取得时候按列来取
    {
        Chatmsg onemsg;
        onemsg.sendId = queryChatHub.value(0).toInt();
        onemsg.targetId = queryChatHub.value(1).toInt();
        onemsg.msgContent = queryChatHub.value(2).toString();
        onemsg.msgtime = queryChatHub.value(3).toString();
        cList.push_back(onemsg);
//        logUserInfo(u);//打印取出的用户信息
    }
    return true;
}

bool UserManager::saveChatMsgToDb(qint32 senderid, qint32 targetid, const QString &chatmsg)
{
    QSqlDatabase dbChatHub=connecToDb();
    QSqlQuery queryChatHub=QSqlQuery(dbChatHub);
    QString sql = QString("INSERT INTO `t_chatmsg` (`f_senderid`, `f_targetid`, `f_msgcontent`) VALUES ('%1', '%2', '%3');").arg(senderid).arg(targetid).arg(chatmsg);
    if (!queryChatHub.exec(sql))
    {
        qDebug()<<"消息入库失败!";
        return false;
    }
    qDebug()<<"消息入库成功!";
    return true;
}

bool UserManager::getUserInfoByUsername(User &user)
{
    auto it=m_allCachedUsers.lower_bound(user);
    if(it->username!=user.username){
        qDebug()<<"通过用户名查询好友信息失败"<<endl;
        return false;
    }
    else {
        user=*it;
//        qDebug()<<it->userid<<userid;
    }
    return true;
}

bool UserManager::getFriendsListByUserName(QString username, QList<friendInfo> &fList)
{
    User user;
    user.username=username;
    auto it=m_allCachedUsers.lower_bound(user);
    if(it->username!=user.username){
        qDebug()<<"通过用户名查询好友信息失败"<<endl;
        return false;
    }
    else {
        fList=it->friends;
//        qDebug()<<it->userid<<userid;
    }
    return true;
}

bool UserManager::loadUsersFromDb()
{
    m_allCachedUsers.clear();
    QSqlDatabase dbChatHub=connecToDb();
    QSqlQuery queryChatHub=QSqlQuery(dbChatHub);
    QString sql="select f_user_id, f_username, f_nickname, f_password,  f_facetype, f_customface, f_gender, f_birthday, f_signature, f_address, f_phonenumber, f_mail, f_teaminfo from t_user";//从表中取出需要的列
    if(!queryChatHub.exec(sql))//查询失败抛出异常
    {
        printf("UserManager::_Query error, dbname: %s", m_strDbName.toStdString().c_str());
        return false;
    }
    while(queryChatHub.next())//一行一行遍历，取出当前行的内容,取得时候按列来取
    {
        User u;
        u.userid = queryChatHub.value(0).toInt();
        u.username = queryChatHub.value(1).toString();
        u.nickname = queryChatHub.value(2).toString();
        u.password = queryChatHub.value(3).toString();
        u.facetype = queryChatHub.value(4).toInt();
        u.customface = queryChatHub.value(5).toString();
        u.gender = queryChatHub.value(6).toInt();
        u.birthday = queryChatHub.value(7).toInt();
        u.signature = queryChatHub.value(8).toString();
        u.address = queryChatHub.value(9).toString();
        u.phonenumber = queryChatHub.value(10).toString();
        u.mail = queryChatHub.value(11).toString();
        u.teaminfo = queryChatHub.value(12).toString();
        loadRelationshipFromDb(u.userid,u.friends);
        m_allCachedUsers.insert(u);
//        logUserInfo(u);//打印取出的用户信息
        //计算当前最大userid
        if (u.userid < GROUPID_BOUBDARY && u.userid > m_baseUserId)
            m_baseUserId = u.userid;
        //计算当前最大群组id
        if (u.userid > GROUPID_BOUBDARY && u.userid > m_baseGroupId)
            m_baseGroupId = u.userid;
    }
    dbChatHub.close();
    return true;
}

bool UserManager::loadRelationshipFromDb(qint32 userid, QList<friendInfo> &fList)
{
    QSqlDatabase dbChatHub=connecToDb();
    QSqlQuery queryChatHub=QSqlQuery(dbChatHub);
    QString sql=QString("SELECT f_user_id1, f_user_id2, f_user1_markname, f_user2_markname, f_user1_teamname, f_user2_teamname FROM t_user_relationship WHERE f_user_id1 = %1 OR f_user_id2 = %2 ").arg(userid).arg(userid);
    if(!queryChatHub.exec(sql))//查询失败抛出异常
    {
        qDebug()<<QString("UserManager::Query error, db: %1").arg(m_strDbName);
        return false;
    }
    while(queryChatHub.next())//一行一行遍历，取出当前行的内容,取得时候按列来取
    {
        qint32 friendid1 = queryChatHub.value(0).toInt();
        qint32 friendid2 = queryChatHub.value(1).toInt();
        QString markname1 = queryChatHub.value(2).toString();
        QString markname2 = queryChatHub.value(3).toString();
        QString teamname1 = queryChatHub.value(4).toString();
        QString teamname2 = queryChatHub.value(5).toString();
        if (teamname1.isEmpty())
            teamname1 = "我的好友";
        if (teamname2.isEmpty())
            teamname2 = "我的好友";
        friendInfo fi;
        if (friendid1 == userid)
        {
            fi.friendid = friendid2;
            fi.markname = markname1;
            fi.teamname = teamname1;
            fList.push_back(fi);
            qDebug()<<QString("userid=%1, friendid=%2").arg(userid).arg(friendid2);
        }
        else
        {
            fi.friendid = friendid1;
            fi.markname = markname2;
            fi.teamname = teamname2;
            fList.push_back(fi);
            qDebug()<<QString("userid=%1, friendid=%2").arg(userid).arg(friendid2);
        }
    }
    return true;
}

void UserManager::logUserInfo(const User &u){
    qDebug() << u.userid << u.username << u.nickname << u.password << u.facetype << u.customface << u.gender
             << u.birthday << u.signature << u.address << u.phonenumber << u.mail << u.teaminfo;
}

QSqlDatabase UserManager::connecToDb()
{
    QSqlDatabase dbChatHub;
    if (QSqlDatabase::contains("chathub")) {
        dbChatHub = QSqlDatabase::database("chathub");
    } else {
        dbChatHub = QSqlDatabase::addDatabase("QMYSQL", "chathub");
    }
    dbChatHub.setHostName(m_strDbServer); //数据库服务器IP
    dbChatHub.setUserName(m_strDbUserName); //数据库用户名
    dbChatHub.setPassword(m_strDbPassword); //数据库密码
    dbChatHub.setDatabaseName(m_strDbName); //使用哪个数据库
    if( !dbChatHub.open() ){ //数据库打开失败
        qDebug() << "Database connection failed: " << dbChatHub.lastError();
    }
    return dbChatHub;//查询绑定要访问的数据库
}
