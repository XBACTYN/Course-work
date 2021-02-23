#ifndef COOLER_H
#define COOLER_H
#include <Element.h>
#include <QRegExp>

class Cooler:public Element
{
private:
    int ventcount;
    QString Sockets;
    int minspeed;
    int maxspeed;
    double airstream;
    int TDP;
    int noise;

public:
    Cooler();
    Cooler(QVector<QString> & data);
    QVector<QString>GetNames();
    QVector<QString>GetValues();
    void RepairSockets(QString & str);
    int getPrice() const;
    void setPrice(int value);
    QUrl getUrl() const;
    void setUrl(const QUrl &value);
    QString getName() const;
    void setName(const QString &value);
    int getVentcount() const;
    void setVentcount(int value);
    QString getSockets() const;
    void setSockets( QString &value);
    int getMinspeed() const;
    void setMinspeed(int value);
    int getMaxspeed() const;
    void setMaxspeed(int value);
    double getAirstream() const;
    void setAirstream(double value);
    int getTDP() const;
    void setTDP(int value);
    int getNoise() const;
    void setNoise(int value);

    void ClearFields();
};

#endif // COOLER_H
