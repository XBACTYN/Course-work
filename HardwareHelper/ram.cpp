#include "ram.h"

int RAM::getPrice() const
{
    return price;
}

void RAM::setPrice(int value)
{
    price = value;
}

QUrl RAM::getUrl() const
{
    return url;
}

void RAM::setUrl(const QUrl &value)
{
    url = value;
}

QString RAM::getName() const
{
    return name;
}

void RAM::setName(const QString &value)
{
    name = value;
}

int RAM::getSumMem() const
{
    return sumMem;
}

void RAM::setSumMem(int value)
{
    sumMem = value;
}

int RAM::getBars() const
{
    return bars;
}

void RAM::setBars(int value)
{
    bars = value;
}

QString RAM::getFormDDR() const
{
    return formDDR;
}

void RAM::setFormDDR(const QString &value)
{
    formDDR = value;
}

QString RAM::getMemType() const
{
    return memType;
}

void RAM::setMemType(const QString &value)
{
    memType = value;
}

QString RAM::getMemFreq() const
{
    return memFreq;
}

void RAM::setMemFreq(const QString &value)
{
    memFreq = value;
}


RAM::RAM(QVector<QString> &data)
{
    setPrice((data[0].toInt()+data[1].toInt())/2);
    setUrl(data[2]);
    setName(data[3]);
    setSumMem(data[4].toInt());
    setBars(data[5].toInt());
    setFormDDR(data[6]);
    setMemType(data[7]);
    setMemFreq(data[8]);
}
