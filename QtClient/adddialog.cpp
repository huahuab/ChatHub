#include "adddialog.h"
#include "ui_adddialog.h"
#include <QMessageBox>

AddDialog::AddDialog(QTcpSocket *skt, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddDialog)
{
    tcpSocket = skt;
    ui->setupUi(this);
}

AddDialog::~AddDialog()
{
    delete ui;
}

void AddDialog::on_conf_button_released()
{
    QString uname = ui->uname_edit->text();
    if(uname.isEmpty() ) {
        QMessageBox::warning(this, "添加失败", "请输入用户名！", QMessageBox::Yes);
    }
    else {

        QString send = "1005 " + uname;
        tcpSocket = new QTcpSocket(this);
        // if(tcpSocket == NULL) qDebug() << "login tcp invalid";
        tcpSocket->abort();
        // 建立与服务器的连接
        tcpSocket->connectToHost("192.168.93.102", 8888);
        if (tcpSocket->waitForConnected(2000))
        {
            qDebug() << "Successfully connected!";

            tcpSocket->write(send.toStdString().c_str());
            tcpSocket->waitForBytesWritten();
            tcpSocket->disconnectFromHost();
    //        tcpSocket->flush();
        }
        else {
            qDebug() << "error in connecting";
            QMessageBox::warning(this, "连接失败", "无法连接到服务器", QMessageBox::Yes);
        }

    }
}

void AddDialog::addSuccessSlot()
{
    QMessageBox::about(this, "添加成功", "该好友已成功添加到好友列表！");
    this->close();
}

void AddDialog::addErrorSlot()
{
    QMessageBox::warning(this, "添加失败", "该用户不存在！", QMessageBox::Yes);
}
