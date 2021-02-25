#include "hdd.h"



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
    if(str.at(0)!=" ")
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
            str+=reg.cap(1)+" ";

    }
    str=" "+str;
    }
}

int HDD::getPrice() const
{
    return price;
}

void HDD::setPrice(const int value)
{
    price=value;
}



QVector<QString>HDD::GetNames()
{
    QVector<QString>temp;
    temp.push_back("Цена, руб");
    temp.push_back("URL-ссылка на товар");
    temp.push_back("Название");
    temp.push_back("Объем, Гб");
    temp.push_back("Интерфейс подключения");
    temp.push_back("Объем буфера обмена");
    temp.push_back("Частота вращения шпинделя, об/мин");
    temp.push_back("Потребляемая мощность при работе, Вт");
    temp.push_back("Уровень шума, дБ");
    return temp;
}

QVector<QString>HDD::GetValues()
{
    QVector<QString>temp;
    temp.push_back(QString::number(getPrice()));
    temp.push_back((url.toString()));
    temp.push_back(getName());
    temp.push_back(QString::number(getCapacity()));
    temp.push_back(getInterface());
    temp.push_back(QString::number(getBuff()));
    temp.push_back(QString::number(getSpeed()));
    temp.push_back(QString::number(getPower()));
    temp.push_back(QString::number(getNoise()));
    return temp;
}

void HDD::ClearFields()
{
    setBuff(0);
    setCapacity(0);
    //setInterface();
    setName("");
    setNoise(0);
    setPower(0);
    setPrice(0);
    setSpeed(0);
    setUrl(QUrl(""));
}
