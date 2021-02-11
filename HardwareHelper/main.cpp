#include "mainwindow.h"
#include "Element.h"
#include <QApplication>
#include <dataloader.h>
int main(int argc, char *argv[])
{
    //test


    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    DataLoader loader;


   // for(int i=0;i<3;++i)// i<9!
   // {
   // loader.Parse1lvl(i,loader.Html,loader.vectorReg,loader.u2array,loader.pages[i]);
   // }

   int k=2;
   loader.RefPrepare(1);//для материнки
   loader.RefPrepare(4);//для кулера
                 QUrl urltest("https://www.e-katalog.ru/ASUS-GEFORCE-RTX-3090-ROG-STRIX-OC.htm");
  //for(int p=0;p<loader.u2arrayI[k];++p)
  // {
  // loader.DownloadPage(loader.Html,loader.u2array[k][p]);
   //qDebug()<<loader.u2array[k][p];
                 loader.DownloadPage(loader.Html,urltest);
                  qDebug()<<urltest;
   loader.Regex2lvl(k,loader.Html,loader.vectorReg2);
  // }

    return a.exec();
}
