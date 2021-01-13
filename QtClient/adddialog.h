#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>
#include <QtNetwork>

namespace Ui {
class AddDialog;
}

class AddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddDialog(QTcpSocket *skt, QWidget *parent = nullptr);
    ~AddDialog();

private slots:
    void on_conf_button_released();

    void addSuccessSlot();
    void addErrorSlot();

private:
    Ui::AddDialog *ui;

    QTcpSocket *tcpSocket;
};

#endif // ADDDIALOG_H
