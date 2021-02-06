#pragma once
#ifndef PROCESSOR_H
#define PROCESSOR_H
#include "Element.h"
#include <QUrl>
class Processor:public Element
{  
public:
    int position;
    int lowPrice;
    int HighPrice;
    QUrl url;
    QString name;//состоит из двух строк
    QString socket;
    int kernels;
    int threads;
    double kerFreq;
    double kerTurbo;
    int techprocess;
    QString iGraphic;
    int TDP;
    int maxMem;
    double _maxMemFreqDDR3; //МГЦ
    double _maxMemFreqDDR4;
                                //Тип линии PCI express. Помним про односторонюю совместимость.
    //QString _link;        //Артикул в магазине! Скорее всего буду использовать как ключ для хеш таблицы.
    //кажется забыл еще потребляемую энергию

    //есть родительское поле QString _article

    Processor();

};

#endif // PROCESSOR_H
