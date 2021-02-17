#include "ssd.h"

int SSD::getPrice() const
{
    return price;
}

void SSD::setPrice(int value)
{
    price = value;
}

QUrl SSD::getUrl() const
{
    return url;
}

void SSD::setUrl(const QUrl &value)
{
    url = value;
}

QString SSD::getName() const
{
    return name;
}

void SSD::setName(const QString &value)
{
    name = value;
}

int SSD::getCapacity() const
{
    return capacity;
}

void SSD::setCapacity(int value)
{
    capacity = value;
}

QString SSD::getForm() const
{
    return form;
}

void SSD::setForm(const QString &value)
{
    form = value;
}

QString SSD::getM2interface() const
{
    return M2interface;
}

void SSD::setM2interface(const QString &value)
{
    M2interface = value;
}

QString SSD::getInterface() const
{
    return interface;
}

void SSD::setInterface(const QString &value)
{
    interface = value;
}

int SSD::getBuff() const
{
    return buff;
}

void SSD::setBuff(int value)
{
    buff = value;
}

int SSD::getWritespeed() const
{
    return writespeed;
}

void SSD::setWritespeed(int value)
{
    writespeed = value;
}

int SSD::getReadspeed() const
{
    return readspeed;
}

void SSD::setReadspeed(int value)
{
    readspeed = value;
}

int SSD::getTBW() const
{
    return TBW;
}

void SSD::setTBW(int value)
{
    TBW = value;
}

SSD::SSD()
{

}

SSD::SSD(QVector<QString> &data)
{
    setPrice((data[0].toInt()+data[1].toInt())/2);
    setUrl(data[2]);
    setName(data[3]);
    setCapacity(data[4].toInt());
    setForm(data[5]);
    setM2interface(data[6]);
    setInterface(data[7]);
    setBuff(data[8].toInt());
    setWritespeed(data[9].toInt());
    setReadspeed(data[10].toInt());
    setTBW(data[11].toInt());
}

QVector<QString>SSD::GetNames()
{
     QVector<QString>temp;
     temp.push_back("Цена, руб");
     temp.push_back("URL-ссылка на товар");
     temp.push_back("Название");
     temp.push_back("Объем, Гб");
     temp.push_back("Форм-фактор");
     temp.push_back("Интерфейс M.2");
     temp.push_back("Интерфейс");
     temp.push_back("Размер буфера обмена, Мб");
     temp.push_back("Скорость записи, Мб/c");
     temp.push_back("Скорость чтения, Мб/c");
     temp.push_back("Наработка на отказ(TBW), Тб");
     return temp;
}

QVector<QString>SSD::GetValues()
{
    QVector<QString>temp;
    temp.push_back(QString::number(getPrice()));
    temp.push_back((url.toString()));
    temp.push_back(getName());
    temp.push_back(QString::number(getCapacity()));
    temp.push_back(getForm());
    temp.push_back(getM2interface());
    temp.push_back(getInterface());
    temp.push_back(QString::number(getBuff()));
    temp.push_back(QString::number(getWritespeed()));
    temp.push_back(QString::number(getReadspeed()));
    temp.push_back(QString::number(getTBW()));
    return temp;
}
