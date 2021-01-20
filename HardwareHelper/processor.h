#pragma once
#ifndef PROCESSOR_H
#define PROCESSOR_H
#include "Element.h"
class Processor:public Element
{  
public:
    int position;
    QString _name;
    QString _manuf;
    QString _socket;
    QString _iGraphic;//или bool
    size_t _kernels;
    size_t _threads;
    size_t _maxMem; //пример 64гб
    size_t _TDP;
    size_t _channels; //количество каналов у оперативы.
    size_t _techprocess; //7,14 нм и прочее.
    double _kerFreq; //частота ядра ГГц
    double _price;
    double _maxMemFreqDDR3; //МГЦ
    double _maxMemFreqDDR4;
                                //Тип линии PCI express. Помним про односторонюю совместимость.
    //QString _link;        //Артикул в магазине! Скорее всего буду использовать как ключ для хеш таблицы.
    //кажется забыл еще потребляемую энергию

    //есть родительское поле QString _article

    //Processor();

};

#endif // PROCESSOR_H
