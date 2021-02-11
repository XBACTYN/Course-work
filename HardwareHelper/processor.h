#pragma once
#ifndef PROCESSOR_H
#define PROCESSOR_H
#include "Element.h"
#include <QUrl>
class Processor
{  
private:
    int price;
    QUrl url;
    QString name;
   // QString name;//состоит из двух строк
    QString socket;
    int cores;
    int threads;
    double freq;
    double turbo;
    int techprocess;
    QString iGraphic;
    int TDP;
    int maxMem;
    double maxMemFreqDDR3; //МГЦ
    double maxMemFreqDDR4;
                                //Тип линии PCI express. Помним про односторонюю совместимость.
    //QString _link;        //Артикул в магазине! Скорее всего буду использовать как ключ для хеш таблицы.
    //кажется забыл еще потребляемую энергию

    //есть родительское поле QString _article
public:
    Processor();
    Processor(QVector<QString>& data);

    QUrl getUrl() const;
    void setUrl(const QUrl &value);
    QString getSocket() const;
    void setSocket(const QString &value);
    int getCores() const;
    void setCores(int value);
    int getThreads() const;
    void setThreads(int value);
    double getFreq() const;
    void setFreq(double value);
    double getTurbo() const;
    void setTurbo(double value);
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
    int getPrice() const;
    void setPrice(int value);
    QString getName() const;
    void setName(const QString &value);
};

#endif // PROCESSOR_H
