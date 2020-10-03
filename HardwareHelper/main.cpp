#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    //main
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
