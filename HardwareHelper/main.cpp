#include "mainwindow.h"
#include "Element.h"
#include <QApplication>
#include <dataloader.h>
int main(int argc, char *argv[])
{
    //test
    //DataLoader loader;
    //loader.ParseProcessors();


    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    DataLoader loader;
    //int pages=3;

    QUrl u=QUrl("https://www.e-katalog.ru/ek-item.php?resolved_name_=GIGABYTE-B450M-S2H-REV--1-0&view_=tbl");

    for(int i=0;i<9;++i)
{
      // int i=8;
   //loader.DownloadPage(loader.Html,u);
  // loader.Regex2lvl(1,loader.Html,loader.vectorReg2);
    loader.Parse1lvl(i,loader.Html,loader.vectorReg,loader.u2array,loader.pages[i]);

    //qDebug()<<"in main"<<loader.u2array[i]<<"\n"<<loader.u2arrayI[i]<<"\n";
    //qDebug()<<loader.Html;
}
   loader.RefMotherboardsPrepare();
    return a.exec();
}
