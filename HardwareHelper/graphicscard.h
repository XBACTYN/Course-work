#ifndef GRAPHICSCARD_H
#define GRAPHICSCARD_H
#include "Element.h"
#include <QUrl>
#include <QString>
class GraphicsCard
{
private:
    int price;
    QUrl url;
    QString name;
    double PCIE;
    int memory;
    QString memoryType;
    int bus;
    int freqGPU;
    int freqMem;
    QString resolution;
    int VGA;
    int DVI;
    int HDMI;
    int DisplayPort;
    int monitors;
    int power;


public:
    GraphicsCard();
    GraphicsCard(QVector<QString>&data);
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
    int getVGA() const;
    void setVGA(int value);
    int getDVI() const;
    void setDVI(int value);
    int getHDMI() const;
    void setHDMI(int value);
    int getMonitors() const;
    void setMonitors(int value);
    int getPower() const;
    void setPower(int value);
    int getPrice() const;
    void setPrice(int value);
    QString getName() const;
    void setName(const QString &value);
    int getDisplayPort() const;
    void setDisplayPort(int value);
};

#endif // GRAPHICSCARD_H
