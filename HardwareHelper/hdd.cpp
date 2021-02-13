#include "hdd.h"

int HDD::getPrice() const
{
    return price;
}

void HDD::setPrice(int value)
{
    price = value;
}

QUrl HDD::getUrl() const
{
    return url;
}

void HDD::setUrl(const QUrl &value)
{
    url = value;
}

QString HDD::getName() const
{
    return name;
}

void HDD::setName(const QString &value)
{
    name = value;
}

int HDD::getCapacity() const
{
    return capacity;
}

void HDD::setCapacity(int value)
{
    capacity = value;
}

QString HDD::getInterface() const
{
    return interface;
}

void HDD::setInterface( QString &value)
{
    RepairInterface(value);
    interface = value;
}

int HDD::getBuff() const
{
    return buff;
}

void HDD::setBuff(int value)
{
    buff = value;
}

int HDD::getSpeed() const
{
    return speed;
}

void HDD::setSpeed(int value)
{
    speed = value;
}

double HDD::getPower() const
{
    return power;
}

void HDD::setPower(double value)
{
    power = value;
}

int HDD::getNoise() const
{
    return noise;
}

void HDD::setNoise(int value)
{
    noise = value;
}

HDD::HDD()
{

}

HDD::HDD(QVector<QString> &data)
{
    setPrice((data[0].toInt()+data[1].toInt())/2);
    setUrl(data[2]);
    setName(data[3]);
    setCapacity(data[4].toInt());
    setInterface(data[5]);
    setBuff(data[6].toInt());
    setSpeed(data[7].toInt());
    setPower(data[8].toDouble());
    setNoise(data[9].toInt());
}

void HDD::RepairInterface(QString &str)
{
    QRegExp reg("R>(.{4,6})<B");
    QString nstr="<BR>";
    nstr+=str;
    nstr.replace("<br>","<BR>");
    str.clear();
    int lastPos = 0;
    while( ( lastPos = reg.indexIn( nstr, lastPos ) ) != -1 )
    {
        lastPos += reg.matchedLength();
            //qDebug()<<reg.cap(1);
            str+=reg.cap(1)+" ";

    }
}
