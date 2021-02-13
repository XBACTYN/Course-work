#include "graphicscard.h"

QUrl GraphicsCard::getUrl() const
{
    return url;
}

void GraphicsCard::setUrl(const QUrl &value)
{
    url = value;
}

double GraphicsCard::getPCIE() const
{
    return PCIE;
}

void GraphicsCard::setPCIE(double value)
{
    PCIE = value;
}

int GraphicsCard::getMemory() const
{
    return memory;
}

void GraphicsCard::setMemory(int value)
{
    memory = value;
}

QString GraphicsCard::getMemoryType() const
{
    return memoryType;
}

void GraphicsCard::setMemoryType(const QString &value)
{
    memoryType = value;
}

int GraphicsCard::getBus() const
{
    return bus;
}

void GraphicsCard::setBus(int value)
{
    bus = value;
}

int GraphicsCard::getFreqGPU() const
{
    return freqGPU;
}

void GraphicsCard::setFreqGPU(int value)
{
    freqGPU = value;
}

int GraphicsCard::getFreqMem() const
{
    return freqMem;
}

void GraphicsCard::setFreqMem(int value)
{
    freqMem = value;
}

QString GraphicsCard::getResolution() const
{
    return resolution;
}

void GraphicsCard::setResolution(const QString &value)
{
    resolution = value;
}

int GraphicsCard::getVGA() const
{
    return VGA;
}

void GraphicsCard::setVGA( int value)
{
    VGA = value;
}

int GraphicsCard::getDVI() const
{
    return DVI;
}

void GraphicsCard::setDVI(int value)
{
    DVI = value;
}

int GraphicsCard::getHDMI() const
{
    return HDMI;
}

void GraphicsCard::setHDMI(int value)
{
    HDMI = value;
}

int GraphicsCard::getMonitors() const
{
    return monitors;
}

void GraphicsCard::setMonitors(int value)
{
    monitors = value;
}

int GraphicsCard::getPower() const
{
    return power;
}

void GraphicsCard::setPower(int value)
{
    power = value;
}

int GraphicsCard::getPrice() const
{
    return price;
}

void GraphicsCard::setPrice(int value)
{
    price = value;
}

QString GraphicsCard::getName() const
{
    return name;
}

void GraphicsCard::setName(const QString &value)
{
    name = value;
}

int GraphicsCard::getDisplayPort() const
{
    return DisplayPort;
}

void GraphicsCard::setDisplayPort(int value)
{
    DisplayPort = value;
}

GraphicsCard::GraphicsCard()
{

}

GraphicsCard::GraphicsCard(QVector<QString> &data)
{
    setPrice((data[0].toInt()+data[1].toInt())/2);
    setUrl(data[2]);
    setName(data[3]);
    setPCIE(data[4].toDouble());
    setMemory(data[5].toInt());
    setMemoryType(data[6]);
    setBus(data[7].toInt());
    setFreqGPU(data[8].toInt());
    setFreqMem(data[9].toInt());
    setResolution(data[10]);
    setVGA(data[11].toInt());
    setDVI(data[12].toInt());
    setHDMI(data[13].toInt());
    setDisplayPort(data[14].toInt());
    setMonitors(data[15].toInt());
    setPower(data[16].toInt());
}
