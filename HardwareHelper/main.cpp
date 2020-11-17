#include "mainwindow.h"
#include "Element.h"
#include <QApplication>
#include <dataloader.h>

int main(int argc, char *argv[])
{
    //test



    QApplication a(argc, argv);
    MainWindow w;
    DataLoader * dataloader=new DataLoader();
    dataloader->getData();

    w.show();
    return a.exec();
}
