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
#include "motherboard.h"
#include "graphicscard.h"
#include "ram.h"
#include "cooler.h"
#include "hdd.h"
#include "ssd.h"
#include "power.h"
#include "case.h"
class DataLoader : public QObject
{
    QNetworkAccessManager* manager;
   // QUrl uarray[9];//массив с адресами первого уровня на разные компоненты

public:
    struct Compatible
    {
        int Price;  //Общая цена
        QString Socket; //Сокет для Проца,материнки
        int FreqDDR4;//параметр для проца,материнки,ОЗУ
        int FreqDDR3;//параметр для проца,материнки,ОЗУ
        QString MotherForm;//параметр для материнки и корпуса
        QString PowerForm;//параметр для БП и корпуса
        QString DDRtype;//Параметр для проца,материнки,ОЗУ
        int MaxFreqRAM;
        //QString SATA;//Параметр для материнки,hdd,ssd,блока питания
        int M2;//параметр для материнки,ssd
        int SATA;
        int USB2;//параметр для материнки,корпуса
        int USB3;//параметр для материнки,корпуса
        int TDP;//параметр для процессора,кулера
        int MinPower;//Общий параметр,основывается на видеокарте. так же hdd и ssd
        //int PCIE
        //int VGA,HDMI/......
    };

    struct Config{
        Processor processor;
        MotherBoard motherboard;
        GraphicsCard graphicscard;
        RAM ram;
        Cooler cooler;
        HDD hdd;
        SSD ssd;
        Power power;
        Case box;

    };
    Compatible demand;
    Config config;
    QUrl uarray[9];
    QVector<QRegExp> vectorReg;//массив регулярок
    QVector<QRegExp> vectorReg2;
    int fields[9];
    QString Html;
    QVector <QVector<QUrl>> u2array;//массив с адресами на дочерние страницы  //массив должен быть двумерным!!!!!!!!!!!!!!!!
    int u2arrayI[9];// ячейка содержит количество ссылок на каждый тип комплектующих. например u2array[0]==81 это 81 url процессоров.
    int pages[9];

    QVector<QString>tempdata;
    QVector<Processor> arrProcessors;
    QVector<MotherBoard> arrMotherboards;
    QVector<GraphicsCard>arrGraphicsCards;
    QVector<RAM>arrRAMs;
    QVector<Cooler>arrCoolers;
    QVector<HDD>arrHDDs;
    QVector<SSD>arrSSDs;
    QVector<Power>arrPowers;
    QVector<Case>arrCases;
    QVector<int>gamerConfig{28,7,43,6,2,0,6,4,4};
    QVector<int>maxSum{0,0,0,0,0,0,0,0,0};
    QVector<QVector<int>>availableIndexes;
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
    DataLoader();
    void DownloadPage(QString & Html,QUrl &url);//test
    void Parse1lvl(int i,QString & Html,QVector<QRegExp>&vectorReg,QVector<QVector<QUrl>>& u2array,int  pages);
    void Regex1lvl(int i,QString & Html,QVector<QRegExp>&vectorReg,QVector<QUrl>&tempVector);
    void Regex2lvl(int i,QString & Html,QVector<QRegExp>&vectorReg2,QVector<QString> &data);
    void ClearElArrays();

    template<class T>
    int BinaryIndex(QVector<T>&arr,int size,const int value);
    void FindAllVariants(int sum,int configType);
    void SortFromCheapest();
    void SortFromMostExpensive();
    void ClearConfig();
    bool ChooseGraphicCard(int index,int sum,int &surplus);
    bool ChooseProcessor(int index,int sum,int &surplus);
    bool ChooseMotherBoard(int index,int sum,int &surplus);
    bool ChooseRAM(int index,int sum,int & surplus);
    bool ChooseSSD(int index,int sum,int & surplus);
    bool ChooseCooler(int index,int sum,int &surplus);
    bool ChoosePower(int index,int sum,int & surplus);
    bool ChooseCase(int index,int sum,int & surplus);
    bool CheckCoolerSoket(QString findSocket,QString coolerSockets);
    void GenerateConfig(int type,int sum);

};


#endif // DOWNLOADER_H
