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


    for(int i=0;i<5;++i)// i<9!
    {
    loader.Parse1lvl(i,loader.Html,loader.vectorReg,loader.u2array,loader.pages[i]);
    }

   int k=4;
   loader.RefPrepare(1);//для материнки
   loader.RefPrepare(4);//для кулера
                QUrl urltest("https://www.e-katalog.ru/ek-item.php?resolved_name_=ID-COOLING-SE-224-XT-BLACK&view_=tbl");
  //for(int p=0;p<loader.u2arrayI[k];++p)
   //{
  // loader.DownloadPage(loader.Html,loader.u2array[k][p]);
  // qDebug()<<loader.u2array[k][p];
                 loader.DownloadPage(loader.Html,urltest);
                  qDebug()<<urltest;
   loader.Regex2lvl(k,loader.Html,loader.vectorReg2);
  // }

    return a.exec();
}
