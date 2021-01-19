#include "mainwindow.h"
#include "Element.h"
#include <QApplication>
#include <dataloader.h>
#include <form.h>
int main(int argc, char *argv[])
{
    //test
    //DataLoader loader;
    //loader.ParseProcessors();


    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    Form f;
    f.show();
    DataLoader loader;
    loader.DownloadPage(loader.Html,loader.uarray[0]);
    loader.Regex1lvl(0,loader.Html,loader.vectorReg,loader.u2array);
    qDebug()<<loader.u2array[0]<<"\n"<<loader.u2arrayI[0];
    return a.exec();
}
