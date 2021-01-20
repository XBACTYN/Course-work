#pragma once
#ifndef MYCONTAINER_H
#define MYCONTAINER_H
#include <QVector>
template <typename T>
class MyContainer{
public:
    QVector <T> _vector;
    MyContainer();
    void AddElem();


};

template<typename T>
void MyContainer<T>::AddElem()
{

}


#endif // MYCONTAINER_H
