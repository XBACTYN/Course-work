#include "cooler.h"

int Cooler::getPrice() const
{
    return price;
}

void Cooler::setPrice(int value)
{
    price = value;
}

QUrl Cooler::getUrl() const
{
    return url;
}

void Cooler::setUrl(const QUrl &value)
{
    url = value;
}

QString Cooler::getName() const
{
    return name;
}

void Cooler::setName(const QString &value)
{
    name = value;
}

int Cooler::getVentcount() const
{
    return ventcount;
}

void Cooler::setVentcount(int value)
{
    ventcount = value;
}

QString Cooler::getSockets() const
{
    return Sockets;
}

void Cooler::setSockets(QString &value)
{
    RepairSockets(value);
    Sockets = value;
}

int Cooler::getMinspeed() const
{
    return minspeed;
}

void Cooler::setMinspeed(int value)
{
    minspeed = value;
}

int Cooler::getMaxspeed() const
{
    return maxspeed;
}

void Cooler::setMaxspeed(int value)
{
    maxspeed = value;
}

double Cooler::getAirstream() const
{
    return airstream;
}

void Cooler::setAirstream(double value)
{
    airstream = value;
}

int Cooler::getTDP() const
{
    return TDP;
}

void Cooler::setTDP(int value)
{
    TDP = value;
}

int Cooler::getNoise() const
{
    return noise;
}

void Cooler::setNoise(int value)
{
    noise = value;
}

Cooler::Cooler()
{

}

void Cooler::RepairSockets(QString &str)
{
    QRegExp reg("R>(.{3,20})(?:/|<B)");
    QString nstr="<BR>";
    nstr+=str;
    nstr+="<BR>";
   // qDebug()<<nstr;
    str.clear();
    int lastPos = 0;
    while( ( lastPos = reg.indexIn( nstr, lastPos ) ) != -1 )
    {
        lastPos += reg.matchedLength();
            //qDebug()<<reg.cap(1);
            str+=reg.cap(1)+" ";

    }
   //qDebug()<<str;

}
