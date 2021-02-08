#include "processor.h"

int Processor::getPosition() const
{
    return position;
}

void Processor::setPosition(int value)
{
    position = value;
}

QUrl Processor::getUrl() const
{
    return url;
}

void Processor::setUrl(const QUrl &value)
{
    url = value;
}

QString Processor::getSocket() const
{
    return socket;
}

void Processor::setSocket(const QString &value)
{
    socket = value;
}

int Processor::getKernels() const
{
    return kernels;
}

void Processor::setKernels(int value)
{
    kernels = value;
}

int Processor::getThreads() const
{
    return threads;
}

void Processor::setThreads(int value)
{
    threads = value;
}

double Processor::getKerFreq() const
{
    return kerFreq;
}

void Processor::setKerFreq(double value)
{
    kerFreq = value;
}

double Processor::getKerTurbo() const
{
    return kerTurbo;
}

void Processor::setKerTurbo(double value)
{
    kerTurbo = value;
}

int Processor::getTechprocess() const
{
    return techprocess;
}

void Processor::setTechprocess(int value)
{
    techprocess = value;
}

QString Processor::getIGraphic() const
{
    return iGraphic;
}

void Processor::setIGraphic(const QString &value)
{
    iGraphic = value;
}

int Processor::getTDP() const
{
    return TDP;
}

void Processor::setTDP(int value)
{
    TDP = value;
}

int Processor::getMaxMem() const
{
    return maxMem;
}

void Processor::setMaxMem(int value)
{
    maxMem = value;
}

double Processor::getMaxMemFreqDDR3() const
{
    return _maxMemFreqDDR3;
}

void Processor::setMaxMemFreqDDR3(double maxMemFreqDDR3)
{
    _maxMemFreqDDR3 = maxMemFreqDDR3;
}

double Processor::getMaxMemFreqDDR4() const
{
    return _maxMemFreqDDR4;
}

void Processor::setMaxMemFreqDDR4(double maxMemFreqDDR4)
{
    _maxMemFreqDDR4 = maxMemFreqDDR4;
}

Processor::Processor(){}



