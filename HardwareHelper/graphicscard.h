#ifndef GRAPHICSCARD_H
#define GRAPHICSCARD_H
#include "Element.h"
#include <QUrl>
#include <QString>
class GraphicsCard:public Element
{
private:
    QUrl url;
    double PCIE;
    int memory;
    QString memoryType;
    int bus;
    int freqGPU;
    int freqMem;
    QString resolution;
    QString VGA;
    QString DVI;
    QString HDMI;
    int monitors;
    int power;


public:
    GraphicsCard();
    QUrl getUrl() const;
    void setUrl(const QUrl &value);
    double getPCIE() const;
    void setPCIE(double value);
    int getMemory() const;
    void setMemory(int value);
    QString getMemoryType() const;
    void setMemoryType(const QString &value);
    int getBus() const;
    void setBus(int value);
    int getFreqGPU() const;
    void setFreqGPU(int value);
    int getFreqMem() const;
    void setFreqMem(int value);
    QString getResolution() const;
    void setResolution(const QString &value);
    QString getVGA() const;
    void setVGA(const QString &value);
    QString getDVI() const;
    void setDVI(const QString &value);
    QString getHDMI() const;
    void setHDMI(const QString &value);
    int getMonitors() const;
    void setMonitors(int value);
    int getPower() const;
    void setPower(int value);
};

#endif // GRAPHICSCARD_H
