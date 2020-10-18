#pragma once
#ifndef PROCESSOR_H
#define PROCESSOR_H
#include "Element.h"
class Processor:public Element
{  
private:
    QString _name;
    QString _manuf;
    QString _socket;
    QString _memType;
    QString _iGraphic;
    size_t _kernels;
    size_t _maxMem;
    size_t _heat;
    size_t _pciExpress;
    size_t _date;
    double _kerFreq;
    double _price;
    double _minMemFreq;
    double _maxMemFreq;
                                //Тип линии PCI express. Помним про односторонюю совместимость.
    bool _multThreading;        //Многопоточность
    //QString _link;
    //QString _vendCode         //Артикул в магазине! Скорее всего буду использовать как ключ для хеш таблицы.
    //кажется забыл еще потребляемую энергию

public:
    Processor();
    Processor(QString name,QString manuf,QString socket,QString memType,
              QString graphic,size_t kernels,size_t maxMem,size_t heat,
              size_t PCI,size_t date,double kerFreq,double price,double minMemF,double maxMemF,bool mthreading):

        _name(name),_manuf(manuf),_socket(socket),_memType(memType),
        _iGraphic(graphic),_kernels(kernels),_maxMem(maxMem),_heat(heat),
        _pciExpress(PCI),_date(date),_kerFreq(kerFreq),_price(price),_minMemFreq(minMemF),
        _maxMemFreq(maxMemF),_multThreading(mthreading){}

    const QString &GetName();
    const QString &GetManuf();
    const QString &GetSocket();
    const QString &GetMemType();
    const QString &GetGraphic();
    size_t GetKernels();
    size_t GetmaxMem();
    size_t GetHeat();
    size_t GetPCI();
    size_t GetDate();
    double GetKerFreq();
    double GetPrice();
    double GetMinMemFreq();
    double GetMaxMemFreq();
    bool GetMultiThreading();


};

#endif // PROCESSOR_H
