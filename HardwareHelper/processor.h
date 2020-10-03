#ifndef PROCESSOR_H
#define PROCESSOR_H
#include "IElement.h"
class Processor:public IElement
{  
public:
    QString _name;              //имя
    QString _manuf;             //производитель
    QString _socket;            //Сокет
    size_t _kerCount;           //Количество ядер
    double _kerFreq;            //Частота ядер
    QString _memType;           //Поддержка типа оперативы
    double _price;              //Цена
    size_t _maxMem;             //Максимально оперативы
    double _minMemFreq;         //Минимальная частота оперативы
    double _maxMemFreq;         //Максимальная частота оперативы
    size_t _heat;               //Тепловыделение
    QString _integGraphic;      //Наличие встроенного графического ядра
    size_t _pciExpress;         //Тип линии PCI express. Помним про односторонюю совместимость.
    bool _multThreading;        //Многопоточность
    size_t _date;               //Год релиза
    //QString _link;
    //QString _vendCode         //Артикул в магазине


    Processor();
};

#endif // PROCESSOR_H
