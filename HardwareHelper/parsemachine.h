#pragma once
#ifndef PARSEMACHINE_H
#define PARSEMACHINE_H
#include "Element.h"
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QFile>
#include <QUrl>
#include <QDebug>
#include <QMap>
class ParseMachine
{

public:
    QMap<QString,Element>map;


    ParseMachine();

    void Insert(QString str,Element el);


};

#endif // PARSEMACHINE_H
