#include "clientwidget.h"
#include "clientwidget.h"
#include "clientwidget.h"
#include "ui_clientwidget.h"
#include "adddialog.h"
#include "revisedialog.h"
#include <QObject>
#include <QDebug>
#include <QMessageBox>

ClientWidget::ClientWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ClientWidget)
{
    // 配置主界面UI
    ui->setupUi(this);
    ui->friend_lable->hide();
    ui->record->hide();
    ui->edit->hide();
    ui->send_button->hide();
    ui->clear_button->hide();
    ui->logo_label->show();

    // 预设IP与端口
//    this->ip = "192.168.93.102";
    this->ip = "192.168.185.102";
    this->client_port = 7777;
    this->server_port = 8888;
    this->islogged = false;

    // 首先弹出登录窗口，获取登录信息
    login = new LoginDialog(client_port, server_port, ip, &tcpSocket);

    connect(login, SIGNAL(tcp_signal()), this, SLOT(connectSlot()));
    connect(login, SIGNAL(login_signal(QString)), this, SLOT(initInfo(QString)));
    connect(this, SIGNAL(pwdwrong_signal()), login, SLOT(pwdwrongSlot()));
    connect(this, SIGNAL(nonex_signal()), login, SLOT(nonexSlot()));
    connect(this, SIGNAL(login_success_signal()), login, SLOT(loginSuccessSlot()));
    login->exec();
    // 如果未完成登录，便不再显示主窗口，直接终止程序
//    if(!islogged) {
//        this->close();
//    }
}

ClientWidget::~ClientWidget()
{
    delete ui;
}

bool ClientWidget::isLogged() {
    return this->islogged;
}

void ClientWidget::connectSlot() {
    qDebug() << "connect the slot";
    if(tcpSocket == NULL) qDebug() << "invalid";
    connect(tcpSocket, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readData()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), \
               this, SLOT(readError(QAbstractSocket::SocketError)));
}

void ClientWidget::initInfo(QString info) {
    qDebug() << "init info:  " << info;
    // 显示自己的昵称
    ui->user_label->setText(nickname);
    QFont *font = new QFont;
    font->setPointSize(14);
    ui->user_label->setFont(*font);
    // 设置表头
    ui->friend_list->setColumnCount(3);
    QStringList list;
    list << "好友昵称" << "状态" <<"未读";
    ui->friend_list->setHorizontalHeaderLabels(list);
    // 只能选中某一行
    ui->friend_list->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->friend_list->setSelectionBehavior(QAbstractItemView::SelectRows);
    // 禁止修改
    ui->friend_list->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // 列宽自适应
    ui->friend_list->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Mock
//    for(int i = 0; i < 10; ++i) {
//        int row = ui->friend_list->rowCount();
//        ui->friend_list->insertRow(row);
//        QString name = "User";
//        name += '0'+i;
//        ui->friend_list->setItem(row,0,new QTableWidgetItem(name));
//        ui->friend_list->setItem(row,1,new QTableWidgetItem("离线"));
//        ui->friend_list->setItem(row,2,new QTableWidgetItem("233"));
//    }

}

void ClientWidget::on_exit_button_released()
{
    if(tcpSocket->isOpen()) tcpSocket->disconnectFromHost();
    if (tcpSocket->state() == QAbstractSocket::UnconnectedState \
            || tcpSocket->waitForDisconnected(1000))
    {
        qDebug() << "disconnected";
    }
    this->close();
}

void ClientWidget::onConnected()
{
    qDebug() << "connected!";
    this->close();
}

void ClientWidget::readError(QAbstractSocket::SocketError)
{
    tcpSocket->disconnectFromHost();
    QMessageBox::warning(this, "连接失败", "无法连接到服务器", QMessageBox::Yes);
}

// 接收服务端的数据，根据头字段进行不同处理
// xxx#xxx...  头字段含义：log登录，all所有记录，mes单条消息，add添加好友，reg注册，rev修改密码，onl上下线提示
void ClientWidget::readData()
{
    qDebug() << "read data:";
    QByteArray buffer = tcpSocket->readAll();
    QString info = buffer;
    if(info.endsWith("\n") )
        info = info.left(info.length()-1);
    qDebug() << info;
//    QString type = info.mid(0, 3); // 功能字段
//    QString ret = info.mid(4); // 剩余字段
//    if(type == "log") dealLogin(ret);
//    else if(type == "mes") dealMessage(ret);
//    else if(type == "all") dealAll(ret);
//    else if(type == "rev") dealRevise(ret);
//    else if(type == "reg") dealRegister(ret);
//    else if(type == "onl") dealOnline(ret);
//    else {
//        qDebug() << "undefined type";
//    }
    QString type = info.mid(0, 4); // 功能字段
    QString ret = info.mid(5); // 剩余字段
    if(type == "1002") dealLogin(ret);
    else if(type == "1100") dealMessage(ret);
    else if(type == "1101") dealAll(ret);
    else if(type == "1005") dealAdd(ret);
    else if(type == "1008") dealRevise(ret);
    else if(type == "1001") dealRegister(ret);
    else if(type == "1006") dealOnline(ret);
    else {
        qDebug() << "undefined type";
    }
}

void ClientWidget::dealLogin(QString info) {
    QStringList ret = QString(info).split(' ');
    // 密码错误
    if(ret[0] == "103") {
        emit pwdwrong_signal();
    }
    // 登录成功后，初始化界面信息
    else if(ret[0] == "0"){
        islogged = true;
        nickname = ret[1];
        id = ret[2];
        emit login_success_signal();
        initInfo(info);
    }
    // 用户不存在
//    else if(info == "102") {
    else {
        emit nonex_signal();
    }
}

void ClientWidget::dealAll(QString info) {
    QStringList ret = QString(info).split(' ');
    qDebug() << ret;
    for(int i = 1; i < ret.length(); ) {
        qDebug() << i << "  " << ret.length();
        // 将id与nickname互相映射
        mNick[ret[i]] = ret[i+1];
        mNid[ret[i+1]] = ret[i];
        // 将id与table的行号互相映射
        int row = ui->friend_list->rowCount();
        mRow[ret[i]] = row;
        mId[row] = ret[i];
        qDebug() << "mapped";
        // 加载好友列表
        ui->friend_list->insertRow(row);
        ui->friend_list->setItem(row,0,new QTableWidgetItem(ret[i+1]));
        if(ret[i+2] == "0") ui->friend_list->setItem(row,1,new QTableWidgetItem("离线"));
        else                ui->friend_list->setItem(row,1,new QTableWidgetItem("在线"));
        ui->friend_list->setItem(row,2,new QTableWidgetItem(ret[i+3]));

        //获取所有聊天记录
        int num = ret[i+3].toInt();
        qDebug() << "num: " << num;
        qDebug() << ret[i+3];
        for(int j = i+4; j < i+4+num; ++j) {
            chats[ret[i]].push_back(ret[j]);
        }
        i += num+4;
    }
}

void ClientWidget::dealMessage(QString info) {
    QStringList ret = QString(info).split(' ');
    chats[ret[1]].push_back(ret[0]);
    // 获取原有的未读消息数目
    int row = mRow[ret[1]];
    int num = ui->friend_list->item(row, 2)->text().toInt();

    ui->friend_list->setItem(row,2,new QTableWidgetItem(QString::number(++num)));

    // 若发送方为与当前窗口一致，则直接更新
    if(ui->friend_lable->text() == mNick[ret[1]] ) {
        ui->friend_list->setItem(row,2,new QTableWidgetItem("0"));
        ui->record->append(ret[0]);
        ui->record->append("\n");
    }

}

void ClientWidget::dealRegister(QString info) {
    if(info == "0") {

        QMessageBox::warning(this->regist, "注册成功", "注册成功", QMessageBox::Yes);
//        QMessageBox::about(this->regist, "注册成功", "注册成功");
        this->regist->close();
    }
    else {
        QMessageBox::warning(this->regist, "注册失败", "输入的用户名已被使用", QMessageBox::Yes);
    }
}

void ClientWidget::dealRevise(QString info) {
    QStringList ret = QString(info).split(' ');
    if(ret[0] == "0") {
        QMessageBox::about(this->revise, "修改成功", "修改成功");
        this->revise->close();
    }
    else {
        QMessageBox::warning(this->revise, "修改失败", "输入的原密码有误！", QMessageBox::Yes);
    }
}

void ClientWidget::dealAdd(QString info) {
    QStringList ret = QString(info).split(' ');
    if(ret[0] == "0") {
        emit add_success_signal();

        mNick[ret[1]] = ret[2];
        mNid[ret[2]] = ret[1];
        int row = ui->friend_list->rowCount();
        mRow[ret[1]] = row;
        mId[row] = ret[1];
        // 加载好友列表
        ui->friend_list->insertRow(row);
        ui->friend_list->setItem(row,0,new QTableWidgetItem(ret[2]));
        // TODO: 正确显示在线情况
//        if(ret[i+2] == "0") ui->friend_list->setItem(row,1,new QTableWidgetItem("离线"));
//        else                ui->friend_list->setItem(row,1,new QTableWidgetItem("在线"));
        ui->friend_list->setItem(row,1,new QTableWidgetItem("离线"));

        ui->friend_list->setItem(row,2,new QTableWidgetItem("0"));
    }
    else emit add_error_signal();
}

void ClientWidget::dealOnline(QString info) {
    qDebug() << "dealing online/offline";
    QStringList ret = QString(info).split(' ');
    QString id = ret[0];
    int row = mRow[id];
    if(ret[1] == "1") ui->friend_list->setItem(row, 1, new QTableWidgetItem("在线"));
    else ui->friend_list->setItem(row, 1, new QTableWidgetItem("离线"));
}

void ClientWidget::on_friend_list_cellClicked(int row, int column)
{
    // 将好友名称显示在右上方
    QString nickname = ui->friend_list->item(row, 0)->text();
    ui->friend_lable->setText(nickname);
    QFont *font = new QFont;
    font->setPointSize(14);
    ui->friend_lable->setFont(*font);

    //打开聊天窗口的同时，将未读数目置零
    ui->friend_list->item(row, 2)->setText("0");

    ui->friend_lable->show();
    ui->record->show();
    ui->edit->show();
    ui->send_button->show();
    ui->clear_button->show();
    ui->logo_label->hide();
    ui->edit->clear();

    // 加载聊天记录
    ui->record->clear();
    QString id = mId[row];
    for(int i = 0; i < chats[id].length(); ++i) {
        // 处理为 "昵称 时间\n消息内容\n" 的排版
        QString dt, context;
        bool flag = false; // 是否处理完时间信息
        for(int j = 0; j < chats[id][i].length(); ++j) {
            if(!flag && chats[id][i][j] == '\n') {
                flag = true;
                continue;
            }
            if(!flag) dt += chats[id][i][j];
            else context += chats[id][i][j];
        }
//        QDateTime time = QDateTime::fromString(dt, "yyyy-MM-ddT")
        ui->record->append(nickname+" "+dt+"\n"+context);
        ui->record->append("\n");
    }
}

void ClientWidget::on_clear_button_released()
{
    ui->edit->clear();
}

void ClientWidget::on_add_button_released()
{
    add = new AddDialog(tcpSocket);
    connect(this, SIGNAL(add_success_signal()), add, SLOT(addSuccessSlot()));
    connect(this, SIGNAL(add_error_signal()), add, SLOT(addErrorSlot()));
    add->exec();
    delete(add);
}

void ClientWidget::on_revise_button_released()
{
    revise = new ReviseDialog(tcpSocket);
    revise->exec();
    delete(revise);
}

void ClientWidget::on_send_button_released()
{
    // 获取当前时间
    QDateTime time = QDateTime::currentDateTime();
    QString send = "1100 ";
    QString contend = ui->edit->toPlainText();
    // TODO：显示自己的昵称
    ui->record->append(nickname+" "+time.toString("yyyy-MM-dd hh:mm:ss")+"\n"+contend);
    ui->record->append("\n");
    QString id = mNid[ui->friend_lable->text()];
    chats[id].push_back(nickname+" "+time.toString("yyyy-MM-dd hh:mm:ss")+"\n"+contend);
    send += contend + " " + id;
    tcpSocket->write(send.toStdString().c_str());
    ui->edit->clear();
}
