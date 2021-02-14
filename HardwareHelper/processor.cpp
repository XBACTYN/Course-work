#include "processor.h"



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

int Processor::getCores() const
{
    return cores;
}

void Processor::setCores(int value)
{
    cores = value;
}

int Processor::getThreads() const
{
    return threads;
}

void Processor::setThreads(int value)
{
    threads = value;
}

double Processor::getFreq() const
{
    return freq;
}

void Processor::setFreq(double value)
{
    freq = value;
}

double Processor::getTurbo() const
{
    return turbo;
}

void Processor::setTurbo(double value)
{
    turbo = value;
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
    return maxMemFreqDDR3;
}

void Processor::setMaxMemFreqDDR3(double value)
{
    maxMemFreqDDR3 = value;
}

double Processor::getMaxMemFreqDDR4() const
{
    return maxMemFreqDDR4;
}

void Processor::setMaxMemFreqDDR4(double value)
{
    maxMemFreqDDR4 = value;
}

int Processor::getPrice() const
{
    return price;
}

void Processor::setPrice(int value)
{
    price = value;
}

QString Processor::getName() const
{
    return name;
}

void Processor::setName(const QString &value)
{
    name = value;
}

Processor::Processor(){

}

Processor::Processor(QVector<QString>& data)
{
    setPrice((data[0].toInt()+data[1].toInt())/2);
    setUrl(QUrl(data[2]));
    setName(data[3]+data[4]);
    setSocket(data[5]);
    setCores(data[6].toInt());
    setThreads(data[7].toInt());
    setFreq(data[8].toDouble());
    setTurbo(data[9].toDouble());
    setTechprocess(data[10].toInt());
    setIGraphic(data[11]);
    setTDP(data[12].toInt());
    setMaxMem(data[13].toInt());
    setMaxMemFreqDDR3(data[14].toInt());
    setMaxMemFreqDDR4(data[15].toInt());
}



