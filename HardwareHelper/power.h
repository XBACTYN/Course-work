#ifndef POWER_H
#define POWER_H
#include "Element.h"

class Power:public Element
{
private:
    int power;
    QString form;
    int diameter;
    int SATA;
    int MOLEX;
    int PCIE;
    int noise;
public:
    Power();
    Power(QVector<QString>& data);
    QVector<QString>GetNames();
    QVector<QString>GetValues();
    int getPrice() const;
    void setPrice(int value);
    QUrl getUrl() const;
    void setUrl(const QUrl &value);
    QString getName() const;
    void setName(const QString &value);
    int getPower() const;
    void setPower(int value);
    QString getForm() const;
    void setForm(const QString &value);
    int getDiameter() const;
    void setDiameter(int value);
    int getSATA() const;
    void setSATA(int value);
    int getMOLEX() const;
    void setMOLEX(int value);
    int getPCIE() const;
    void setPCIE(int value);
    int getNoise() const;
    void setNoise(int value);
};

#endif // POWER_H
