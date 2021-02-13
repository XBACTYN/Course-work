#ifndef HDD_H
#define HDD_H
#include <QString>
#include <QUrl>

class HDD
{
private:
    int price;
    QUrl url;
    QString name;
    int capacity;
    QString interface;
    int buff;
    int speed;
    double power;
    int noise;
public:
    HDD();
    HDD(QVector<QString>& data);
    void RepairInterface(QString & str);
    int getPrice() const;
    void setPrice(int value);
    QUrl getUrl() const;
    void setUrl(const QUrl &value);
    QString getName() const;
    void setName(const QString &value);
    int getCapacity() const;
    void setCapacity(int value);
    QString getInterface() const;
    void setInterface( QString &value);
    int getBuff() const;
    void setBuff(int value);
    int getSpeed() const;
    void setSpeed(int value);
    double getPower() const;
    void setPower(double value);
    int getNoise() const;
    void setNoise(int value);
};

#endif // HDD_H
