#include "case.h"

int Case::getPrice() const
{
    return price;
}

void Case::setPrice(int value)
{
    price = value;
}

QUrl Case::getUrl() const
{
    return url;
}

void Case::setUrl(const QUrl &value)
{
    url = value;
}

QString Case::getName() const
{
    return name;
}

void Case::setName(const QString &value)
{
    name = value;
}

QString Case::getForm() const
{
    return form;
}

void Case::setForm(const QString &value)
{
    form = value;
}

QString Case::getMotherForm() const
{
    return motherForm;
}

void Case::setMotherForm(const QString &value)
{
    motherForm = value;
}

QString Case::getPowerForm() const
{
    return powerForm;
}

void Case::setPowerForm(const QString &value)
{
    powerForm = value;
}

int Case::getSlotform2_5() const
{
    return slotform2_5;
}

void Case::setSlotform2_5(int value)
{
    slotform2_5 = value;
}

int Case::getSlotform3_5() const
{
    return slotform3_5;
}

void Case::setSlotform3_5(int value)
{
    slotform3_5 = value;
}

int Case::getMaxVents() const
{
    return maxVents;
}

void Case::setMaxVents(int value)
{
    maxVents = value;
}

int Case::getUSB2() const
{
    return USB2;
}

void Case::setUSB2(int value)
{
    USB2 = value;
}

int Case::getUSB3() const
{
    return USB3;
}

void Case::setUSB3(int value)
{
    USB3 = value;
}

Case::Case()
{

}

Case::Case(QVector<QString> &data)
{
    setPrice((data[0].toInt()+data[1].toInt())/2);
    setUrl(data[2]);
    setName(data[3]);
    setForm(data[4]);
    setMotherForm(data[5]);
    setPowerForm(data[6]);
    setSlotform3_5(data[7].toInt());
    setSlotform2_5(data[8].toInt());
    setMaxVents(data[9].toInt());
    setUSB2(data[10].toInt());
    setUSB3(data[11].toInt());
}
