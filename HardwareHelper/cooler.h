#ifndef COOLER_H
#define COOLER_H
#include <QString>
#include <QUrl>
#include <QRegExp>

class Cooler
{
private:
    int price;
    QUrl url;
    QString name;
    int ventcount;
    QString Sockets;
    int minspeed;
    int maxspeed;
    double airstream;
    int TDP;
    int noise;

public:
    Cooler();
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
};

#endif // COOLER_H
