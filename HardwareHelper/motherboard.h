#pragma once
#ifndef MOTHERBOARD_H
#define MOTHERBOARD_H
#include "Element.h"
class MotherBoard:public Element
{
private:
    QString socket;
    QString form;
    int DDR3count;
    int DDR4count;
    QString formDDR;
    int maxFreq;
    int maxMem;
    QString VGA;
    QString DVI;
    QString HDMI;
    QString DispayPort;
    QString audio;
    int SATA3;
    int M2;
    double PCIE;
    int USB2;
    int USB3;
    int USBC;

public:
    MotherBoard();
    MotherBoard(QVector<QString> & data);
    QVector<QString>GetNames();
    QVector<QString>GetValues();
    QUrl getUrl() const;
    void setUrl(const QUrl &value);
    QString getSocket() const;
    void setSocket(const QString &value);
    QString getForm() const;
    void setForm(const QString &value);
    int getDDR4count() const;
    void setDDR4count(int value);
    QString getFormDDR() const;
    void setFormDDR(const QString &value);
    int getMaxFreq() const;
    void setMaxFreq(int value);
    int getMaxMem() const;
    void setMaxMem(int value);
    QString getVGA() const;
    void setVGA(const QString &value);
    QString getDVI() const;
    void setDVI(const QString &value);
    QString getHDMI() const;
    void setHDMI(const QString &value);
    QString getDispayPort() const;
    void setDispayPort(const QString &value);
    QString getAudio() const;
    void setAudio(const QString &value);
    int getSATA3() const;
    void setSATA3(int value);
    int getM2() const;
    void setM2(int value);
    double getPCIE() const;
    void setPCIE(double value);
    int getUSB2() const;
    void setUSB2(int value);
    int getUSB3() const;
    void setUSB3(int value);
    int getUSBC() const;
    void setUSBC(int value);
    int getPrice() const;
    void setPrice(int value);
    QString getName() const;
    void setName(const QString &value);
    int getDDR3count() const;
    void setDDR3count(int value);
};

#endif // MOTHERBOARD_H
