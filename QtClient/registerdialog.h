#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include <QtNetwork>

namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(QTcpSocket *skt, QWidget *parent = nullptr);
    ~RegisterDialog();

private slots:
    void on_back_button_released();

    void on_confirm_button_released();

private:
    Ui::RegisterDialog *ui;

    QTcpSocket *tcpSocket;


};

#endif // REGISTERDIALOG_H
