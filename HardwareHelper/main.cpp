#include "mainwindow.h"
#include "Element.h"
#include <QApplication>
#include <dataloader.h>
#include <form.h>
int main(int argc, char *argv[])
{
    //experimental
    //DataLoader loader;
    //loader.ParseProcessors();


    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    Form f;
    f.show();
    DataLoader loader;
    loader.DownloadPage(0,loader.vectorHtml);
    loader.Regex1lvl(0,loader.vectorHtml,loader.vectorReg);
    return a.exec();
}
