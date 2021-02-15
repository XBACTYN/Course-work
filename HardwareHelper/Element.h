#pragma once
#ifndef ELEMENT_H
#define ELEMENT_H
#include <QString>
#include <QUrl>
class Element{


public:
    int price;
    QUrl url; //замена на string
    QString name;
    int arrsize;
    virtual QVector<QString>GetNames()=0;
    virtual QVector<QString>GetValues()=0;

    Element(){}
   // ~Element(){}
};

#endif // IELEMENT_H
