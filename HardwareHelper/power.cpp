#include "power.h"

int Power::getPrice() const
{
    return price;
}

void Power::setPrice(int value)
{
    price = value;
}

QUrl Power::getUrl() const
{
    return url;
}

void Power::setUrl(const QUrl &value)
{
    url = value;
}

QString Power::getName() const
{
    return name;
}

void Power::setName(const QString &value)
{
    name = value;
}

int Power::getPower() const
{
    return power;
}

void Power::setPower(int value)
{
    power = value;
}

QString Power::getForm() const
{
    return form;
}

void Power::setForm(const QString &value)
{
    form = value;
}

int Power::getDiameter() const
{
    return diameter;
}

void Power::setDiameter(int value)
{
    diameter = value;
}

int Power::getSATA() const
{
    return SATA;
}

void Power::setSATA(int value)
{
    SATA = value;
}

int Power::getMOLEX() const
{
    return MOLEX;
}

void Power::setMOLEX(int value)
{
    MOLEX = value;
}

int Power::getPCIE() const
{
    return PCIE;
}

void Power::setPCIE(int value)
{
    PCIE = value;
}

int Power::getNoise() const
{
    return noise;
}

void Power::setNoise(int value)
{
    noise = value;
}

Power::Power()
{

}

Power::Power(QVector<QString> &data)
{
    setPrice((data[0].toInt()+data[1].toInt())/2);
    setUrl(data[2]);
    setName(data[3]);
    setPower(data[4].toInt());
    setForm(data[5]);
    setDiameter(data[6].toInt());
    setSATA(data[7].toInt());
    setMOLEX(data[8].toInt());
    setPCIE(data[9].toInt());
    setNoise(data[10].toInt());
}

QVector<QString>Power::GetNames()
{
    QVector<QString>temp;
    temp.push_back("Цена, руб");
    temp.push_back("URL-ссылка на товар");
    temp.push_back("Название");
    temp.push_back("Мощность, Вт");
    temp.push_back("Форм-фактор");
    temp.push_back("Диаметр вентилятора, мм");
    temp.push_back("Максимально разъемов SATA");
    temp.push_back("Максимально разъемов MOLEX");
    temp.push_back("Максимально разъемов PCI-E");
    temp.push_back("Уровень шума");
    return temp;
}
QVector<QString>Power::GetValues()
{
    QVector<QString>temp;
    temp.push_back(QString::number(getPrice()));
    temp.push_back((url.toString()));
    temp.push_back(getName());
    temp.push_back(QString::number(getPower()));
    temp.push_back(getForm());
    temp.push_back(QString::number(getDiameter()));
    temp.push_back(QString::number(getSATA()));
    temp.push_back(QString::number(getMOLEX()));
    temp.push_back(QString::number(getPCIE()));
    temp.push_back(QString::number(getNoise()));
    return temp;
}
