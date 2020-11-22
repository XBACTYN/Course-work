#ifndef DATALOADER_H
#define DATALOADER_H

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QUrl>
#include <QTextCodec>
#include <QFile>
#include <QEventLoop>

class DataLoader : public QObject
{

    QNetworkAccessManager* manager;
    QUrl url;

public:
    DataLoader();
    void ParsePage();//test

};


#endif // DOWNLOADER_H
