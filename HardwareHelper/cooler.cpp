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

void Cooler::setSockets( QString &value)
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

Cooler::Cooler(QVector<QString> &data)
{
    setPrice((data[0].toInt()+data[1].toInt())/2);
    setUrl(data[2]);
    setName(data[3]);
    setVentcount(data[4].toInt());
    setSockets(data[5]);
    setMinspeed(data[6].toInt());
    setMaxspeed(data[7].toInt());
    setAirstream(data[8].toDouble());
    setTDP(data[9].toInt());
    setNoise(data[10].toInt());
}

void Cooler::RepairSockets(QString &str)
{
    QRegExp reg("R>(.{3,20})(?:/|<B)");
    QString nstr="<BR>";
    nstr+=str;
    nstr+="<BR>";
    str.clear();
    int lastPos = 0;
    while( ( lastPos = reg.indexIn( nstr, lastPos ) ) != -1 )
    {
        lastPos += reg.matchedLength();
            str+=reg.cap(1)+" ";

    }
}

QVector<QString>Cooler::GetNames()
{
    QVector<QString>temp;
    temp.push_back("Цена, руб");
    temp.push_back("URL-ссылка на товар");
    temp.push_back("Название");
    temp.push_back("Количество вентиляторов");
    temp.push_back("Поддерживаемые сокеты");
    temp.push_back("Минимальные обороты, об/мин");
    temp.push_back("Максимальные обороты, об/мин");
    temp.push_back("Макс. воздушный поток, CF/M");
    temp.push_back("Максимальный TDP");
    temp.push_back("Уровень шума, дБ");
    return temp;
}
QVector<QString>Cooler::GetValues()
{
    QVector<QString>temp;
    temp.push_back(QString::number(getPrice()));
    temp.push_back((url.toString()));
    temp.push_back(getName());
    temp.push_back(QString::number(getVentcount()));
    temp.push_back(getSockets());
    temp.push_back(QString::number(getMinspeed()));
    temp.push_back(QString::number(getMaxspeed()));
    temp.push_back(QString::number(getAirstream()));
    temp.push_back(QString::number(getTDP()));
    temp.push_back(QString::number(getNoise()));
    return temp;
}

void Cooler::ClearFields()
{
    setAirstream(0);
    setMaxspeed(0);
    setMinspeed(0);
    setName("");
    setNoise(0);
    setPrice(0);
   // setSockets()
    setTDP(0);
    setUrl(QUrl(""));
    setVentcount(0);
}
