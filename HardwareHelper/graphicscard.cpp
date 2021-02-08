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

QString GraphicsCard::getVGA() const
{
    return VGA;
}

void GraphicsCard::setVGA(const QString &value)
{
    VGA = value;
}

QString GraphicsCard::getDVI() const
{
    return DVI;
}

void GraphicsCard::setDVI(const QString &value)
{
    DVI = value;
}

QString GraphicsCard::getHDMI() const
{
    return HDMI;
}

void GraphicsCard::setHDMI(const QString &value)
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

GraphicsCard::GraphicsCard()
{

}
