#pragma once
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
#include "processor.h"

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
    int fields[9];
    QString Html;
    QVector <QVector<QUrl>> u2array;//массив с адресами на дочерние страницы  //массив должен быть двумерным!!!!!!!!!!!!!!!!!!!!!!!!
    int u2arrayI[9];// ячейка содержит количество ссылок на каждый тип комплектующих. например u2array[0]==81 это 81 url процессоров.
    int pages[9];
    //как вариант QVector<QVector
    QVector<Processor> arrProcessors;

    //Element * elptr=arrProcessors;
    void SetRegexProcessor();
    void RefPrepare(int i); //i-номер векторов комплектущих. 1-видеокарта, 4-кулер...
    void SetRegexMotherBoard();
    void SetRegexGraphicsCard();
    void SetRegexRAM();
    void SetRegexCooler();
    void RepairCooler(QString & str);
    void SetRegexHDD();
    void RepairHDD(QString & str);
    void SetRegexSSD();
    void SetRegexPower();
    void SetRegexCase();
    //НАПОМИНАНИЕ! Если не парсится сам элемент,вместо него выводить в консоль адрес.
    DataLoader();
    void DownloadPage(QString & Html,QUrl &url);//test
    void Parse1lvl(int i,QString & Html,QVector<QRegExp>&vectorReg,QVector<QVector<QUrl>>& u2array,int  pages);
    void Regex1lvl(int i,QString & Html,QVector<QRegExp>&vectorReg,QVector<QUrl>&tempVector);
    void Parse2lvl();
    void Regex2lvl(int i,QString & Html,QVector<QRegExp>&vectorReg2);
};


#endif // DOWNLOADER_H
