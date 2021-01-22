#ifndef DATALOADER_H
#define DATALOADER_H

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QUrl>
#include <QTextCodec>
#include <QFile>
#include <QEventLoop>
#include <QString>
#include <QVector>
#include <QRegExp>

class DataLoader : public QObject
{
    //QString url;
    QNetworkAccessManager* manager;
   // QUrl uarray[9];//массив с адресами первого уровня на разные компоненты

public:
    //QVector<QString> vectorHtml;//массив со страницами первого уровня в формате строк.
   //int vectorHtmlc;
    QUrl uarray[9];
    QVector<QRegExp> vectorReg;//массив регулярок
    QVector<QRegExp> vectorReg2;
    int vectorRegc; //под сомнением
    QString Html;
    QVector <QVector<QUrl>> u2array;//массив с адресами на дочерние страницы  //массив должен быть двумерным!!!!!!!!!!!!!!!!!!!!!!!!
    int u2arrayI[9];// ячейка содержит количество ссылок на каждый тип комплектующих. например u2array[0]==81 это 81 url процессоров.
    int pages[9];
    void SetRegexProcessor();
    DataLoader();
    void DownloadPage(QString & Html,QUrl &url);//test
    void Parse1lvl(int i,QString & Html,QVector<QRegExp>&vectorReg,QVector<QVector<QUrl>>& u2array,int  pages);
    void Regex1lvl(int i,QString & Html,QVector<QRegExp>&vectorReg,QVector<QUrl>&tempVector);
    void Parse2lvl();
    void Regex2lvl(int i,QString & Html,QVector<QRegExp>&vectorReg2);
};


#endif // DOWNLOADER_H
