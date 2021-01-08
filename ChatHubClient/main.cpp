#include "loginwindow.h"
#include "mainwindow.h"
#include "singlechat.h"
#include "groupchat.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginWindow w;
    w.show();
    MainWindow mw;
    mw.show();
    SingleChat sg;
    sg.show();
    GroupChat gp;
    gp.show();
    return a.exec();
}
