#include "mainwindow.h"
#include "Element.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    //test


    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
