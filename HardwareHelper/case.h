#ifndef CASE_H
#define CASE_H
#include "Element.h"
class Case:public Element
{
private:
    QString form;
    QString motherForm;
    QString powerForm;
    int slotform2_5;
    int slotform3_5;
    int maxVents;
    int USB2;
    int USB3;
public:
    Case();
    Case(QVector<QString>& data);
    QVector<QString>GetNames();
    QVector<QString>GetValues();
    int getPrice() const;
    void setPrice(int value);
    QUrl getUrl() const;
    void setUrl(const QUrl &value);
    QString getName() const;
    void setName(const QString &value);
    QString getForm() const;
    void setForm(const QString &value);
    QString getMotherForm() const;
    void setMotherForm(const QString &value);
    QString getPowerForm() const;
    void setPowerForm(const QString &value);
    int getSlotform2_5() const;
    void setSlotform2_5(int value);
    int getSlotform3_5() const;
    void setSlotform3_5(int value);
    int getMaxVents() const;
    void setMaxVents(int value);
    int getUSB2() const;
    void setUSB2(int value);
    int getUSB3() const;
    void setUSB3(int value);
};

#endif // CASE_H
