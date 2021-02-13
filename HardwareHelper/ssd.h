#ifndef SSD_H
#define SSD_H
#include <QString>
#include <QUrl>

class SSD
{
private:
    int price;
    QUrl url;
    QString name;
    int capacity;
    QString form;
    QString M2interface;
    QString interface;
    int buff;
    int writespeed;
    int readspeed;
    int TBW;

public:
    SSD();
    SSD(QVector<QString>& data);
    int getPrice() const;
    void setPrice(int value);
    QUrl getUrl() const;
    void setUrl(const QUrl &value);
    QString getName() const;
    void setName(const QString &value);
    int getCapacity() const;
    void setCapacity(int value);
    QString getForm() const;
    void setForm(const QString &value);
    QString getM2interface() const;
    void setM2interface(const QString &value);
    QString getInterface() const;
    void setInterface(const QString &value);
    int getBuff() const;
    void setBuff(int value);
    int getWritespeed() const;
    void setWritespeed(int value);
    int getReadspeed() const;
    void setReadspeed(int value);
    int getTBW() const;
    void setTBW(int value);
};

#endif // SSD_H
