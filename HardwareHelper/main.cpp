#include "mainwindow.h"
#include "Element.h"
#include <QApplication>
#include <dataloader.h>
#include <form.h>
int main(int argc, char *argv[])
{
    //test
    DataLoader loader;
    loader.ParsePage();


    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    Form f;
    f.show();

    return a.exec();
}
