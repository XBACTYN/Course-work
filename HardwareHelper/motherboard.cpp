#include "motherboard.h"



QUrl MotherBoard::getUrl() const
{
    return url;
}

void MotherBoard::setUrl(const QUrl &value)
{
    url = value;
}

QString MotherBoard::getSocket() const
{
    return socket;
}

void MotherBoard::setSocket(const QString &value)
{
    socket = value;
}

QString MotherBoard::getForm() const
{
    return form;
}

void MotherBoard::setForm(const QString &value)
{
    form = value;
}

int MotherBoard::getDDR4count() const
{
    return DDR4count;
}

void MotherBoard::setDDR4count(int value)
{
    DDR4count = value;
}

QString MotherBoard::getFormDDR() const
{
    return formDDR;
}

void MotherBoard::setFormDDR(const QString &value)
{
    formDDR = value;
}

int MotherBoard::getMaxFreq() const
{
    return maxFreq;
}

void MotherBoard::setMaxFreq(int value)
{
    maxFreq = value;
}

int MotherBoard::getMaxMem() const
{
    return maxMem;
}

void MotherBoard::setMaxMem(int value)
{
    maxMem = value;
}

QString MotherBoard::getVGA() const
{
    return VGA;
}

void MotherBoard::setVGA(const QString &value)
{
    VGA = value;
}

QString MotherBoard::getDVI() const
{
    return DVI;
}

void MotherBoard::setDVI(const QString &value)
{
    DVI = value;
}

QString MotherBoard::getHDMI() const
{
    return HDMI;
}

void MotherBoard::setHDMI(const QString &value)
{
    HDMI = value;
}

QString MotherBoard::getDispayPort() const
{
    return DispayPort;
}

void MotherBoard::setDispayPort(const QString &value)
{
    DispayPort = value;
}

QString MotherBoard::getAudio() const
{
    return audio;
}

void MotherBoard::setAudio(const QString &value)
{
    audio = value;
}

int MotherBoard::getSATA3() const
{
    return SATA3;
}

void MotherBoard::setSATA3(int value)
{
    SATA3 = value;
}

int MotherBoard::getM2() const
{
    return M2;
}

void MotherBoard::setM2(int value)
{
    M2 = value;
}

double MotherBoard::getPCIE() const
{
    return PCIE;
}

void MotherBoard::setPCIE(double value)
{
    PCIE = value;
}

int MotherBoard::getUSB2() const
{
    return USB2;
}

void MotherBoard::setUSB2(int value)
{
    USB2 = value;
}

int MotherBoard::getUSB3() const
{
    return USB3;
}

void MotherBoard::setUSB3(int value)
{
    USB3 = value;
}

int MotherBoard::getUSBC() const
{
    return USBC;
}

void MotherBoard::setUSBC(int value)
{
    USBC = value;
}

int MotherBoard::getPrice() const
{
    return price;
}

void MotherBoard::setPrice(int value)
{
    price = value;
}

QString MotherBoard::getName() const
{
    return name;
}

void MotherBoard::setName(const QString &value)
{
    name = value;
}

int MotherBoard::getDDR3count() const
{
    return DDR3count;
}

void MotherBoard::setDDR3count(int value)
{
    DDR3count = value;
}

MotherBoard::MotherBoard()
{

}

MotherBoard::MotherBoard(QVector<QString>& data)
{
    setPrice((data[0].toInt()+data[1].toInt())/2);
    setUrl(QUrl(data[2]));
    setName(data[3]);
    setSocket(data[4]);
    setForm(data[5]);
    setDDR3count(data[6].toInt());
    setDDR4count(data[7].toInt());
    setFormDDR(data[8]);
    setMaxFreq(data[9].toInt());
    setMaxMem(data[10].toInt());
    setVGA(data[11]);
    setDVI(data[12]);
    setHDMI(data[13]);
    setDispayPort(data[14]);
    setAudio(data[15]);
    setSATA3(data[16].toInt());
    setM2(data[17].toInt());
    setPCIE(data[18].toDouble());
    setUSB2(data[19].toInt());
    setUSB3(data[20].toInt());
    setUSBC(data[21].toInt());

}

QVector<QString> MotherBoard::GetNames()
{
    QVector<QString> temp;
    temp.push_back("Цена, руб");
    temp.push_back("URL-ссылка на товар");
    temp.push_back("Название");
    temp.push_back("Сокет(разъем)");
    temp.push_back("Форм-фактор");
    temp.push_back("Макс. планок RAM DDR3");
    temp.push_back("Макс. планок RAM DDR4");
    temp.push_back("Форма RAM");
    temp.push_back("Макс. тактовая частота RAM, МГц");
    temp.push_back("Макс. объем памяти, Гб");
    temp.push_back("Наличие разъема VGA");
    temp.push_back("Наличие разъема DVI");
    temp.push_back("Наличие разъема HDMI");
    temp.push_back("Наличие разъема DisplayPort");
    temp.push_back("Аудиочип");
    temp.push_back("Портов SATA3");
    temp.push_back("Разъем M.2");
    temp.push_back("Версия PCI-E");
    temp.push_back("Портов USB v2");
    temp.push_back("Портов USB v3");
    temp.push_back("Портов USB-C");
    return temp;
}

QVector<QString> MotherBoard::GetValues()
{
    QVector<QString> temp;
    temp.push_back(QString::number(getPrice()));
    temp.push_back((url.toString()));
    temp.push_back(getName());
    temp.push_back(getSocket());
    temp.push_back(getForm());
    temp.push_back(QString::number(getDDR3count()));
    temp.push_back(QString::number(getDDR4count()));
    temp.push_back(getFormDDR());
    temp.push_back(QString::number(getMaxFreq()));
    temp.push_back(QString::number(getMaxMem()));
    temp.push_back(getVGA());
    temp.push_back(getDVI());
    temp.push_back(getHDMI());
    temp.push_back(getDispayPort());
    temp.push_back(getAudio());
    temp.push_back(QString::number(getSATA3()));
    temp.push_back(QString::number(getM2()));
    temp.push_back(QString::number(getPCIE()));
    temp.push_back(QString::number(getUSB2()));
    temp.push_back(QString::number(getUSB3()));
    temp.push_back(QString::number(getUSBC()));
    return temp;
}
