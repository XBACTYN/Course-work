#pragma once
#ifndef PARSEMACHINE_H
#define PARSEMACHINE_H
#include "Element.h"
#include <dataloader.h>
class ParseMachine
{

public:
    QMap<QString,Element>map;


    ParseMachine();

    void Insert(QString str,Element el);




};

#endif // PARSEMACHINE_H
