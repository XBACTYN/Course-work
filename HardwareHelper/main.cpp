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
    //int pages=3;

    for(int i=0;i<9;++i)
{
      // int i=8;
    //loader.DownloadPage(loader.Html,loader.uarray[i]);
    loader.Parse1lvl(i,loader.Html,loader.vectorReg,loader.u2array,loader.pages[i]);

    qDebug()<<"in main"<<loader.u2array[i]<<"\n"<<loader.u2arrayI[i]<<"\n";
}
    return a.exec();
}
