#ifndef SINGLECHAT_H
#define SINGLECHAT_H

#include <QWidget>

namespace Ui {
class SingleChat;
}

class SingleChat : public QWidget
{
    Q_OBJECT

public:
    explicit SingleChat(QWidget *parent = nullptr);
    ~SingleChat();

private:
    Ui::SingleChat *ui;
};

#endif // SINGLECHAT_H
