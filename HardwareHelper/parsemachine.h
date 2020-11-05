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
class ParseMachine
{

public:
    QHash <QString,Element>_hash;

    ParseMachine();
};

#endif // PARSEMACHINE_H
