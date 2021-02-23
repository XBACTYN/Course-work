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



    return a.exec();
}
