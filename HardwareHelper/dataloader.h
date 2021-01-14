#ifndef DATALOADER_H
#define DATALOADER_H

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QUrl>
#include <QTextCodec>
#include <QFile>
#include <QEventLoop>
#include <QString>
#include <QVector>

class DataLoader : public QObject
{
    QString url;
    QNetworkAccessManager* manager;
    QUrl uarray[9];
    QVector<QString> vector;
public:
    DataLoader();
    void ParsePage();//test
    void ParseProcessors();
};


#endif // DOWNLOADER_H
