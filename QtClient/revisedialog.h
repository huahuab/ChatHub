#ifndef REVISEDIALOG_H
#define REVISEDIALOG_H

#include <QDialog>
#include <QtNetwork>

namespace Ui {
class ReviseDialog;
}

class ReviseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReviseDialog(QTcpSocket *skt, QWidget *parent = nullptr);
    ~ReviseDialog();

private slots:
    void on_back_button_released();

    void on_confirm_button_released();

private:
    Ui::ReviseDialog *ui;
    QTcpSocket *tcpSocket;
};

#endif // REVISEDIALOG_H
