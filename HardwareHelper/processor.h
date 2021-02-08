#pragma once
#ifndef PROCESSOR_H
#define PROCESSOR_H
#include "Element.h"
#include <QUrl>
class Processor:public Element
{  
private:
    int position;
    //int lowPrice;
    //int HighPrice;
    QUrl url;
   // QString name;//состоит из двух строк
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
public:
    Processor();

    int getPosition() const;
    void setPosition(int value);
    QUrl getUrl() const;
    void setUrl(const QUrl &value);
    QString getSocket() const;
    void setSocket(const QString &value);
    int getKernels() const;
    void setKernels(int value);
    int getThreads() const;
    void setThreads(int value);
    double getKerFreq() const;
    void setKerFreq(double value);
    double getKerTurbo() const;
    void setKerTurbo(double value);
    int getTechprocess() const;
    void setTechprocess(int value);
    QString getIGraphic() const;
    void setIGraphic(const QString &value);
    int getTDP() const;
    void setTDP(int value);
    int getMaxMem() const;
    void setMaxMem(int value);
    double getMaxMemFreqDDR3() const;
    void setMaxMemFreqDDR3(double maxMemFreqDDR3);
    double getMaxMemFreqDDR4() const;
    void setMaxMemFreqDDR4(double maxMemFreqDDR4);
};

#endif // PROCESSOR_H
