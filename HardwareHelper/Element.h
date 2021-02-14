#pragma once
#ifndef ELEMENT_H
#define ELEMENT_H
#include <QString>
class Element{
protected:
    int price;
    QString name;

public:
    QString GetName()const{return name;}
    int GetPrice()const{return price;}


    Element(){}
   // ~Element(){}
};

#endif // IELEMENT_H
