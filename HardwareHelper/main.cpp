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

    for(int i=0;i<8;++i)
{
    loader.DownloadPage(loader.Html,loader.uarray[i]);
    loader.Regex1lvl(i,loader.Html,loader.vectorReg,loader.u2array);
    qDebug()<<"in main"<<loader.u2array[i]<<"\n"<<loader.u2arrayI[i]<<"\n";
}
    return a.exec();
}
