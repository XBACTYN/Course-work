#include "Element.h"
#include <QApplication>
#include <dataloader.h>
#include <modelviewwidget.h>

int main(int argc, char *argv[])
{
    //experimental



    QApplication a(argc, argv);
    ModelViewWidget w;
    w.show();
    srand(time(0));
    for(int i =0;i<10;++i)
        qDebug()<<rand()%2;


    return a.exec();
}
