#include "singlechat.h"
#include "ui_singlechat.h"

SingleChat::SingleChat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SingleChat)
{
    ui->setupUi(this);
}

SingleChat::~SingleChat()
{
    delete ui;
}
