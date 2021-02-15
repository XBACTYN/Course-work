#pragma once
#ifndef PROCESSOR_H
#define PROCESSOR_H
#include "Element.h"
class Processor:public Element
{  
private:

    QString socket;
    int cores;
    int threads;
    double freq;
    double turbo;
    int techprocess;
    QString iGraphic;
    int TDP;
    int maxMem;
    double maxMemFreqDDR3;
    double maxMemFreqDDR4;
                                // PCI express. Помним про односторонюю совместимость.



public:

    Processor();
    Processor(QVector<QString>& data);
    QVector<QString>GetNames();
    QVector<QString>GetValues();
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
