#include "motherboard.h"

int MotherBoard::getPosition() const
{
    return position;
}

void MotherBoard::setPosition(int value)
{
    position = value;
}

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

MotherBoard::MotherBoard()
{
    
}
