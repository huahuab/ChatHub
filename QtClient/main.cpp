#include "clientwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ClientWidget w;
    if(w.isLogged() ) w.show();
    return a.exec();
}
