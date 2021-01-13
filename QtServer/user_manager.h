#ifndef USER_MANAGER_H
#define USER_MANAGER_H
/**
 *  管理所有的用户信息，初始信息从数据库中加载, user_manager.h
 *  huahuab 2020.01.09
 **/
#pragma once
#include <stdint.h>
#include <QString>
#include <list>
#include <mutex>
#include <set>
#include <atomic>
#include <QString>
#include <QList>
#include <QPair>
#include <QSqlDatabase>
#include <QSqlQuery>
using namespace std;

#define GROUPID_BOUBDARY   0x0FFFFFFF

#define DEFAULT_TEAMNAME  "My Friends"

enum FRIEND_OPERATION
{
    FRIEND_OPERATION_ADD,
    FRIEND_OPERATION_DELETE
};

struct friendInfo
{
    qint32  friendid;
    QString  markname;
    QString  teamname;
};

struct userStatus
{
    QString username;
    bool status=false;
public:
    userStatus(QString name,bool s=false);
};

struct Chatmsg
{
    qint32 sendId;
    qint32 targetId;
    QString msgContent;
    QString msgtime;
};

//用户或者群
struct User
{
    qint32          userid;      //0x0FFFFFFF以上是群号，以下是普通用户
    QString         username;    //群账户的username也是群号userid的字符串形式
    QString         password;
    QString         nickname;    //群账号为群名称
    qint32          facetype;
    QString         customface;
    QString         customfacefmt;//自定义头像格式
    qint32          gender;
    qint32          birthday;
    QString         signature;
    QString         address;
    QString         phonenumber;
    QString         mail;
    /*
    个人用户好友分组信息，对于群账户则为空，例如:
    [{"teamname": "我的好友"}, {"teamname": "我的同事"}, {"teamname": "企业客户"}]
    */
    QString          teaminfo;       //对于普通用户，为分组信息；对于群组则为空
    qint32          ownerid;        //对于群账号，为群主userid
    QList<friendInfo> friends;

public:
    bool operator< (const User& user) const;//重载小于号
};

class UserManager final
{
public:
    UserManager();
    ~UserManager();
    UserManager(const UserManager& rhs) = delete;//禁止拷贝构造
    UserManager& operator=(const UserManager& rhs) = delete;

    bool init(const char* dbServer, const char* dbUserName, const char* dbPassword, const char* dbName);
    bool getUsersList(QMap<qint32,userStatus> *userStatus);
    bool checkUser(QString username,QString password);
    bool getUseridByName(const QString &username,qint32 &userid);

    bool addUser(QString username,QString nickname,QString password,qint32 &userid);
    bool makeFriendRelationshipInDB(qint32 smallUserid, qint32 greaterUserid);

    bool releaseFriendRelationshipInDBAndMemory(qint32 smallUserid, qint32 greaterUserid);
    bool updateUserRelationshipInMemory(qint32 userid, qint32 target, FRIEND_OPERATION operation);
    bool addFriendToUser(qint32 userid, qint32 friendid);
    bool deleteFriendToUser(qint32 userid, qint32 friendid);

    bool isFriend(qint32 userid, qint32 friendid);

    //TODO: 这类都是更新用户信息的接口，将来可以考虑统一起来
    bool updateUserInfoInDb(qint32 userid, const User& newuserinfo);
    bool modifyUserPasswordByUserName(const QString &username, const QString &oldPassword, const QString &newPassword);
    //将内存和数据库中的某个用户的分组信息改成新的newteaminfo
    bool updateUserTeamInfoInDbAndMemory(qint32 userid, const QString& newteaminfo);
    bool deleteTeam(qint32 userid, const QString& deletedteamname);
    bool modifyTeamName(qint32 userid, const QString& newteamname, const QString& oldteamname);

    //更新用户好友备注名
    bool updateMarknameInDb(qint32 userid, qint32 friendid, const QString& newmarkname);
    //移动好友至其他分组
    bool moveFriendToOtherTeam(qint32 userid, qint32 friendid, const QString& newteamname);

    bool addGroup(const char* groupname, qint32 ownerid, qint32& groupid);

    //聊天消息入库
    bool getChatMsgFromDbByUsername(QString username,QString fusername,QList<Chatmsg> &cList);
    bool saveChatMsgToDb(qint32 senderid, qint32 targetid, const QString& chatmsg);

    //TODO: 当用户越来越多，并发量越来越多的时候，这个系列的函数效率高吗？
    bool getUserInfoByUsername(User& user);
    bool getUserInfoByUserId(qint32 userid, User& u);
    bool getUserInfoByUserId(qint32 userid, User*& u);
    bool getFriendInfoByUserId(qint32 userid, QList<User>& friends);
    bool getFriendsListByUserName(QString username,QList<friendInfo>& fList);
    //获取好友的备注名
    bool getFriendMarknameByUserId(qint32 userid1, qint32 friendid, QString& markname);
    bool getTeamInfoByUserId(qint32 userid, QString& teaminfo);

private:
    void logUserInfo(const User &u);
    QSqlDatabase connecToDb();
    bool loadUsersFromDb();
    bool loadRelationshipFromDb(qint32 userid, QList<friendInfo> &fList);

private:
    std::atomic_int     m_baseUserId{0};        //m_baseUserId, 取数据库里面userid最大值，新增用户在这个基础上递增
    std::atomic<int>    m_baseGroupId{0x0FFFFFFF};
    set<User>           m_allCachedUsers;
    mutex               m_mutex;

    QString             m_strDbServer;
    QString             m_strDbUserName;
    QString             m_strDbPassword;
    QString             m_strDbName;
};
#endif // USER_MANAGER_H
