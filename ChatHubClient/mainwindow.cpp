#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    ui->profile_lable->setPixmap(QPixmap(":/img/profile.jpg"));
//    ui->profile_lable->setScaledContents(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}
