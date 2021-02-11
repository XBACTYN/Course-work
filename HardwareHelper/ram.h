#ifndef RAM_H
#define RAM_H
#include <QString>
#include <QUrl>

class RAM
{
private:
    int price;
    QUrl url;
    QString name;
    int sumMem;
    int bars;
    QString formDDR;
    QString memType;
    QString memFreq;
public:
    RAM();
    RAM(QVector<QString>& data);
    int getPrice() const;
    void setPrice(int value);
    QUrl getUrl() const;
    void setUrl(const QUrl &value);
    QString getName() const;
    void setName(const QString &value);
    int getSumMem() const;
    void setSumMem(int value);
    int getBars() const;
    void setBars(int value);
    QString getFormDDR() const;
    void setFormDDR(const QString &value);
    QString getMemType() const;
    void setMemType(const QString &value);
    QString getMemFreq() const;
    void setMemFreq(const QString &value);
};

#endif // RAM_H
